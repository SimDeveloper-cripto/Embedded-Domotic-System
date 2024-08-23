// 1. git clone https://github.com/Not-Nik/raylib-zig.git [raylib-zig (c) Nikolas Wipper 2023]
// 2. ./project_setup.ps1
// 3. cd Project && zig build run

const std = @import("std");
const rl = @import("raylib");
const raygui = @cImport({
    @cInclude("raygui.h");
});
const Utils = @import("utils.zig").Utils;
const Interface = @import("interface.zig").Interface;
const ClientSocket = @import("client_socket.zig").ClientSocket;

// GENERAL
// TODO: FIGURE OUT WHY CLIENT DISCONNECTS AFTER JUST ONE REQUEST

// ARDUINO
// TODO: BEFORE PUSHING TO REPO, COMMENT SSID AND PASS

// ZIG
// TODO: WHATCH OUT FOR MEMORY LEAKS ON ALLOCATORS
// TODO: BEAUTIFY THE INTERFACE

pub fn main() anyerror!void {
    rl.initWindow(600, 350, "House Lights Control Panel - Made with Raylib");
    defer rl.closeWindow();
    rl.setTargetFPS(60);

    var btnStates: [4]bool = .{ false, false, false, false };
    var buttonLabels = [_][*c]const u8{
        "KITCHEN: OFF", // BUTTON #1
        "BED ROOM: OFF", // BUTTON #2
        "BATH ROOM: OFF", // BUTTON #3
        "LIVING ROOM: OFF", // BUTTON #4
    };

    var allocator = std.heap.page_allocator;
    const rects = try Interface.getButtonArray(&allocator, 600, 350, 120, 50, 20);
    defer allocator.free(rects);

    raygui.GuiSetStyle(raygui.DEFAULT, raygui.TEXT_COLOR_NORMAL, Utils.RaylibColorToCInt(rl.Color{ .r = 0, .g = 0, .b = 0, .a = 255 }));

    // CONNECT TO SERVER SOCKET
    var client_socket = try ClientSocket.init(&allocator, "127.0.0.1", 6969);
    defer client_socket.deinit();

    // MAIN LOOP
    while (!rl.windowShouldClose()) {
        rl.beginDrawing();
        defer rl.endDrawing();
        rl.clearBackground(rl.Color.ray_white);

        const welcomeLabel = "Control Panel Home Page! ";
        const welcomeTextSize = 20.0;
        const welcomeTextWidth = rl.measureText(welcomeLabel, welcomeTextSize);
        rl.drawText(welcomeLabel, @divFloor(600 - welcomeTextWidth, 2), 40, welcomeTextSize, rl.Color.black);

        var i: usize = 0;
        while (i < rects.len) {
            const rect = rects[i];
            if (raygui.GuiButton(rect, buttonLabels[i]) != 0) {
                btnStates[i] = !btnStates[i];

                if (btnStates[i]) {
                    buttonLabels[i] = switch (i) {
                        0 => "KITCHEN: ON",
                        1 => "BED ROOM: ON",
                        2 => "BATH ROOM: ON",
                        3 => "LIVING ROOM: ON",
                        else => buttonLabels[i],
                    };
                } else {
                    buttonLabels[i] = switch (i) {
                        0 => "KITCHEN: OFF",
                        1 => "BED ROOM: OFF",
                        2 => "BATH ROOM: OFF",
                        3 => "LIVING ROOM: OFF",
                        else => buttonLabels[i],
                    };
                }

                try client_socket.sendJSON("led", btnStates[i], i + 1);
            }
            i += 1;
        }
    }
}
