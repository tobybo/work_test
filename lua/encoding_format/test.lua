
local function os_excute(opt)
    local t = io.popen(opt)
    print("lua: ", opt)
    local ret = t:read("*all")
    t:close()
    print("result: ", ret)
end

os_excute("python3 /root/work/test/lua/encoding_format/test.py '呵呵'")
