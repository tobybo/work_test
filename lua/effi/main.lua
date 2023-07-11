
local effil = require("effil")

share_table = share_table

local function test()
    print("this is main.lua")
    print("load effil ", effil and "true" or "failed")
    if not effil then return end
    share_table = effil.table()
    regist_share_table("share_table", share_table)
    lock_share_table()
    table.insert(share_table, {name = "toby", age = 18})
    unlock_share_table()
    print("[M] insert share table done")
    while true do
    end
end

function format_log(fmt, ...)
    return string.format(fmt, ...)
end

function STACK(msg)
    local stack = debug.traceback(msg, 2)
    for level in string.gmatch(stack, "[^%c]+") do
        print(format_log("[LUA] %s", level))
    end
    print(format_log("[LuaError] %s", string.gsub(stack, "\n\t?", "#LF#")))
end

coroutine.wrap(function()
    xpcall(test, STACK)
end)()

