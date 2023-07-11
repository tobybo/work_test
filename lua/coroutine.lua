
local tab = {
    1,2,3,
    a = 1,
    b = 2,
    c = 3,
}

local done = false
local coroutine_1 = function()
    for k,v in pairs(tab) do
        print("k: ",k, "v: ", v)
        coroutine.yield()
    end
    done = true
end

local main = function()
    local co = coroutine.create(coroutine_1)
    local keys = {2, "c", "b", 2, "a", 3}
    local idx = 1
    while not done do
        coroutine.resume(co)
        print("delete key, ", keys[idx])
        tab[keys[idx]] = nil
        idx = idx + 1
        tab.idx = idx
    end
end


main()


