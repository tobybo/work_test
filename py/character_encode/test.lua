
local function os_excute(opt)
    local t = io.popen(opt)
    ngx.log(ngx.ERR, "lua: ", opt)
    local ret = t:read("*all")
    t:close()
    ngx.log(ngx.ERR, "result: ", ret)
end

os_excute("python3 /test.py '呵呵'")

