const std = @import("std");
const raygui = @cImport({
    @cInclude("raygui.h");
});

pub const Interface = struct {
    // RETURNS A MATRIX OF 4 BUTTONS
    pub fn getButtonArray(allocator: *std.mem.Allocator, screenWidth: i32, screenHeight: i32, buttonWidth: i32, buttonHeight: i32, padding: i32) ![]raygui.Rectangle {
        const tempX = @divFloor(screenWidth - (buttonWidth * 2 + padding), 2);
        const tempY = @divFloor(screenHeight - (buttonHeight * 2 + padding), 2);

        const xPos = @as(f32, @floatFromInt(tempX));
        const yPos = @as(f32, @floatFromInt(tempY));
        const buttonWidthF32 = @as(f32, @floatFromInt(buttonWidth));
        const buttonHeightF32 = @as(f32, @floatFromInt(buttonHeight));
        const paddingF32 = @as(f32, @floatFromInt(padding));

        // Dynamically allocate the Array
        var rects = try allocator.alloc(raygui.Rectangle, 4);
        rects[0] = raygui.Rectangle{ .x = xPos, .y = yPos, .width = buttonWidthF32, .height = buttonHeightF32 };
        rects[1] = raygui.Rectangle{ .x = xPos + buttonWidthF32 + paddingF32, .y = yPos, .width = buttonWidthF32, .height = buttonHeightF32 };
        rects[2] = raygui.Rectangle{ .x = xPos, .y = yPos + buttonHeightF32 + paddingF32, .width = buttonWidthF32, .height = buttonHeightF32 };
        rects[3] = raygui.Rectangle{ .x = xPos + buttonWidthF32 + paddingF32, .y = yPos + buttonHeightF32 + paddingF32, .width = buttonWidthF32, .height = buttonHeightF32 };

        return rects;
    }
};
