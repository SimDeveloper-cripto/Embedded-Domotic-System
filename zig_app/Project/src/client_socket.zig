const std = @import("std");
const os = std.os;
const net = std.net;
const json = std.json;
const debug = std.debug;

pub const ClientSocket = struct {
    stream: net.Stream,
    allocator: *std.mem.Allocator,
    address: []const u8,
    port: u16,

    pub fn init(allocator: *std.mem.Allocator, address: [:0]const u8, port: u16) !ClientSocket {
        var self = ClientSocket{
            .stream = undefined,
            .allocator = allocator,
            .address = address,
            .port = port,
        };

        try self.reconnect();
        return self;
    }

    fn reconnect(self: *ClientSocket) !void {
        const address_buffer = try net.Address.parseIp4(self.address, self.port);
        self.stream = try net.tcpConnectToAddress(address_buffer);
    }

    pub fn deinit(self: *ClientSocket) void {
        _ = self.stream.close();
    }

    pub fn sendJSON(self: *ClientSocket, object: []const u8, state: bool, number: usize) !void {
        const alloc = std.heap.page_allocator;
        const value = if (state) "HIGH" else "LOW";

        var buffer = std.ArrayList(u8).init(alloc);
        defer buffer.deinit();

        try buffer.appendSlice("{\"object\":\"");
        try buffer.appendSlice(object);
        try buffer.appendSlice("\",\"value\":\"");
        try buffer.appendSlice(value);
        try buffer.appendSlice("\",\"number\":");

        var num_buf: [20]u8 = undefined;
        const num_str = try std.fmt.bufPrint(&num_buf, "{}", .{number});
        try buffer.appendSlice(num_str);
        try buffer.appendSlice("}");

        // SEND DATA
        const json_data = try buffer.toOwnedSlice();
        defer self.allocator.free(json_data);
        try self.stream.writeAll(json_data);

        // GET RESPONSE
        var res_buffer: [1024]u8 = undefined;
        const res_size = try self.stream.read(&res_buffer);
        if (res_size > 0) {
            const res_json = res_buffer[0..res_size];
            std.debug.print("Received from Server: {s}\n", .{res_json});
        } else {
            std.debug.print("No response received from Server. :(\n", .{});
        }

        // CLOSE THE STREAM AND RECONNECT
        self.stream.close();
        try self.reconnect();
    }
};
