const xo = @cImport({
    @cInclude("xo.h");
    @cInclude("stdio.h");
});

pub fn main() anyerror!void {
    // _ = xo.printf("from c");
    _ = xo.start();
}
