
local tab = {
    a = 2,
    b = 3,
}

--[[
for i = 1, 3 do
    local c, d = next(tab)
    if not c or not d then
        print("nil val")
    else
        tab[c] = nil
        print("k: "..c.." val: "..d)
    end
end
]]

--[[
local last_key
for i = 1, 10 do
    local key, val = next(tab, last_key)
    last_key = key
    print(key, val)
end
]]

local tab1 = {
    [1] = 1,
    [3] = 3,
}

