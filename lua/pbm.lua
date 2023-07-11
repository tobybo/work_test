local function disk(cx, cy, r)
    return function(x, y)
        return (x - cx)^2 + (y - cy)^2 <= r^2
    end
end

local function rect(left, right, bottom, up)
    return function(x, y)
        return left <= x and x <= right and bottom <= y and y <= up
    end
end

local function difference(r1, r2)
    return function(x, y)
        return r1(x, y) and not r2(x, y)
    end
end

local function translate(r, dx, dy)
    return function(x, y)
        return r(x - dx, y - dy)
    end
end

local file
local wt = function(...)
    file:write(...)
end
local function plot(r, M, N)
    wt("P1\n", M, " ", N, "\n")
    for i = 1, N do
        local y = (N - i * 2) / N
        for j = 1, M do
            local x = (j * 2 - M) / M
            wt(r(x, y) and "1" or 0)
        end
        wt("\n")
    end
end

local filename = arg[1]
file = io.open(filename, "w+")
local c1 = disk(0, 0, 1)
plot(difference(c1, translate(c1, 0.3, 0)), 500, 500)
file:close()
