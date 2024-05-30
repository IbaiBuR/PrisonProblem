const boxes = @import("boxes.zig");
const utils = @import("utils.zig");

const RUNS: usize = 100000;

fn run(reboots: *[RUNS]u8) void {

    for(0..RUNS) |i| {
        while (true) {
            const passed: bool = boxes.select(boxes.init());

            if (!passed) {
                reboots[i] += 1;
            }
            else {
                break;
            }
        }
    }

    utils.print_stats(reboots);
}

pub fn main() !void {
    var reboots: [RUNS]u8 = undefined;

    for (&reboots) |*reboot| {
        reboot.* = 0;
    }

    run(&reboots);
}
