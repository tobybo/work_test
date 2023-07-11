
local str = arg[1]

-- local pos = utf8.offset(str, -1)
-- print(str:len())
-- print(utf8.len(str))
-- print(pos)
-- print(str:sub(1, pos + 2))
-- local pos = utf8.offset(str, -2)
-- print(pos)
-- print(str:sub(1, pos + 2))


function split_utf8(str, least)
    local len_u = utf8.len(str)
    if len_u <= least then
        return {str}
    end
    local res = {str}
    local tail
    local pos = -1
    while len_u > least do
        tail = utf8.offset(str, pos)
        table.insert(res, str:sub(1, tail - 1))
        pos = pos - 1
        len_u = len_u - 1
    end
    return res
end

function split_utf8_2(str, least)
    local len_u = utf8.len(str)
    if len_u <= least then
        return {str}
    end
    local res = {}
    local start_pos = utf8.offset(str, least + 1)
    local sp_str = str:sub(start_pos)
    for p, c in utf8.codes(sp_str) do
        table.insert(res, str:sub(1, start_pos - 1 + p - 1))
        --print(p, " ", c)
    end
    table.insert(res, str)
    return res
end

function split_utf8_3(str, least)
    local len = str:len()
    if len <= least then
        return {str}
    end
    local res = {}
    least, start_pos = utf8.len(str, 1, least)
    local start_pos = utf8.offset(str, least + 1)
    local sp_str = str:sub(start_pos)
    for p, c in utf8.codes(sp_str) do
        table.insert(res, str:sub(1, start_pos - 1 + p - 1))
        --print(p, " ", c)
    end
    table.insert(res, str)
    return res
end


local res = split_utf8(str, 3)
for _, val in ipairs(res) do
    print(val)
end

res = split_utf8_2(str, 3)
for _, val in ipairs(res) do
    print(val)
end

res = split_utf8_3(str, 3)
for _, val in ipairs(res) do
    print(val)
end

-- local loop_times = 100*10000
-- local t0,t1
-- local count = 0
-- t0 = os.clock()
-- for i = 1, loop_times do
--     split_utf8(str, 3)
-- end
-- t1 = os.clock()
-- print("time1: ", t1 - t0)
--
-- t0 = os.clock()
-- for i = 1, loop_times do
--     split_utf8_2(str, 3)
-- end
-- t1 = os.clock()
-- print("time2: ", t1 - t0)

--print(utf8.codepoint(str, 1, str:len()))
