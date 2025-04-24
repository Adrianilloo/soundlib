# vim: set sts = 2 ts = 8 sw = 2 tw = 99 et:
import sys
from ambuild2 import run

parser = run.BuildParser(sourcePath = sys.path[0], api = '2.2')
add_arg = parser.options.add_argument

add_arg('--hl2sdk-root', type = str, dest = 'hl2sdk_root', default = None, help = "Root search folder for HL2SDKs")
add_arg('--mms-path', type = str, dest = 'mms_path', default = None, help = "Path to Metamod:Source")
add_arg('--sm-path', type = str, dest = 'sm_path', default = None, help = "Path to SourceMod")
add_arg('--enable-debug', action = 'store_const', const = '1', dest = 'debug', help = "Enable debugging symbols")
add_arg('--enable-optimize', action = 'store_const', const = '1', dest = 'opt', help = "Enable optimization")
add_arg('-s', '--sdks', default = 'all', dest = 'sdks', help = "Build against specified SDKs;"
	" valid args are 'all', 'present', or comma-delimited list of engine names (default: %default)")
add_arg('--targets', type = str, dest = 'targets', default = None,
	help = "Override the target architecture (use commas to separate multiple targets)")

parser.Configure()
