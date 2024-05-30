const builtin = @import("builtin");
const std = @import("std");

const print = std.debug.print;
const debugging: bool = builtin.mode == .Debug;

pub fn debug_print(comptime format: []const u8, args: anytype) void {
    if (debugging) {
        print(format, args);
    }
}

pub fn print_stats(reboots: []u8) void {
    var total_reboots: u64 = 0;
    var max_reboots: u8 = 0;
    var min_reboots: u8 = 255;

    for (reboots) |reboot| {
        total_reboots += reboot;
        max_reboots = @max(max_reboots, reboot);
        min_reboots = @min(min_reboots, reboot);
    }

    const avg_reboots = total_reboots / reboots.len;

    print("\nStatistics:\n\tTotal: {}\n\t Avg : {}\n\t Max : {}\n\t Min : {}\n", .{ total_reboots, avg_reboots, max_reboots, min_reboots });
}
