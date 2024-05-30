const std = @import("std");
const builtin = @import("builtin");
const utils = @import("utils.zig");

pub fn init() [100]u8 {
    var prng = std.rand.DefaultPrng.init(@as(u64, @bitCast(std.time.milliTimestamp())));
    var numbers: [100]u8 = undefined;

    for (0..100) |i| {
        numbers[i] = @intCast(i);
    }

    prng.random().shuffle(u8, &numbers);
    return numbers;
}

pub fn select(boxes: [100]u8) bool {
    for (0..100) |prisoner| {
        utils.debug_print("Prisoner: {}\n", .{prisoner});

        var count: u8 = 0;
        var current_index: u8 = @intCast(prisoner);
        var found = false;

        while (count < 50 and !found) : (count += 1) {
            const value = boxes[current_index];

            utils.debug_print("Box {:02} - Number {:02}\n", .{ current_index, value });

            if (prisoner == value) {
                found = true;
            } else {
                current_index = value;
            }
        }

        if (!found) {
            utils.debug_print("Failed!\n", .{});
            return false;
        }
    }

    return true;
}
