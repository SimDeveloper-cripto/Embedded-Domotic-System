const std = @import("std");
const rl = @import("raylib");

pub const Utils = struct {
    // UTILITY FUNCTION TO GENERATE A RANDOM COLOR FOR BUTTONS
    pub fn getRandomColor(rng: *std.rand.DefaultPrng) rl.Color {
        const r = @as(u8, @intCast(rng.next() % 256));
        const g = @as(u8, @intCast(rng.next() % 256));
        const b = @as(u8, @intCast(rng.next() % 256));
        return rl.Color{ .r = r, .g = g, .b = b, .a = 255 };
    }

    // UTILITY FUNCTION TO CONVERT RAYLIB COLOR TO ZIG'S C_INT
    pub fn RaylibColorToCInt(color: rl.Color) c_int {
        const r: u32 = @as(u32, @intCast(color.r));
        const g: u32 = @as(u32, @intCast(color.g));
        const b: u32 = @as(u32, @intCast(color.b));
        const a: u32 = @as(u32, @intCast(color.a));
        const value: u32 = (r << 24) | (g << 16) | (b << 8) | a;
        return @intCast(value);
    }
};
