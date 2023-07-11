
local co_ply

function main_loop()
    while true do
        sleep(1)
        if not co_ply then
            co_ply = coroutine.running()
            coroutine.resume(co_ply)
        end
    end
end

function loop_ply()
    local co_ply = coroutine.running()
    coroutine.yield(co_ply)
end

function main()
    local co_a = coroutine.create(main_loop)
    coroutine.resume(co_a)
end

function main2()
    local co_b = coroutine.create(test)
    coroutine.resume(co_b)
end

function test()
    if co_ply then
        coroutine.resume(co_ply)
    end
end

-- local co = coroutine.create(function() print "hello, im a coroutine" end)
-- print(coroutine.status(co))

local add = function(param1, param2)
    local param3 = coroutine.yield(param1 + param2)
    return param1 + param2 + param3
end
-- 创建协程 co
local co = coroutine.create(add)
-- 开始协程的运行 co
local ret, val = coroutine.resume(co, 1, 9)
print(ret, val)

coroutine.yield()

-- 唤醒主动挂起的协程 co
local ret, val = coroutine.resume(co, 2)
print(ret, val)
co = coroutine.create(add)
local ret, val = coroutine.resume(co, 1)
print(ret, val)
