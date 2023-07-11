local tab = setmetatable({}, {__mode="k"})

local a = {b = {}}

tab[a.b] = 1

a.b = nil

for k, v in pairs(tab) do
    print(v)
end
