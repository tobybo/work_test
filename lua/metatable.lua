--元方法 __index 在访问子表没有的字段的情况下会触发
--注意：在给子表没有的字段赋值的情况下会触发__newindex 不会触发 __index
--      lua元方法调用过程中还是允许触发元方法的，所以要用rawset,rawget来避免死循环
local _mt = {}
_mt.__newindex = function(tab, k, v)
    print(" from __index ", k)
    rawset(tab, k, v)
end

local data = {}
setmetatable(data, _mt)

data.hello = "world"
data.test = nil
data.hello = nil

