
import re

pattern_name = r'^GM_CMDS\[[\'\"](.*)[\'\"]]'
pattern_param = r'=function\(self,(.*)\)'

param = 'GM_CMDS["server_tm"] = function(self)'

ret_name = re.findall(pattern_name, param.replace(" ", ""))

if ret_name:
    for val in ret_name:
        print(val)
        print(type(val))

ret_param = re.findall(pattern_param, param.replace(" ", ""))

if ret_param:
    for val in ret_param:
        print(val)
        print(type(val))

if re.search(r"^end.*", "end\n"):
    print("find end succ")
