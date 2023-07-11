

local lib = get_func_tab()

local tab = {}
local meta = getmetatable(tab)
print(meta)
lib.new(tab)
print(tab.a)

