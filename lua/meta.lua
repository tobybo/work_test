
local id = 0
local create = function()
    id = id + 1
    return setmetatable({id = id}, {__index = {idx = -id}})
end

local tbs = {}
for i = 1, 10 do
    table.insert(tbs, create())
end

for _, v in pairs(tbs) do
    if type(v) == "table" then
        print(string.format("id,%s", v.id))
    end
end

local tab = setmetatable({_proxy = {}}, {__newindex = function(t,k,v)
    print("k,%s, v,%s", k, v)
    t._proxy[k] = v
end, __pairs = function(t)
    return next, t._proxy, nil
end})


tab[1] = 10
tab[1] = nil
tab[1] = 11
tab[2] = 12

for i, v in pairs(tab) do
    print("i,%s, v,%s", i, v)
end

local old_meta = {__index = function()return "old" end}
local new_meta = {__index = function()return "new" end}
local a = setmetatable({}, old_meta)
print(a[1])
setmetatable(a, new_meta)
print(a[1])


