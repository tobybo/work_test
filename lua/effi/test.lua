
local effi = require("effil")

local share = effi.table()

local func = function()
end

local mantb = {a = 10}

thr = nil

local co = coroutine.create(function()
    thr = effi.thread(function()
        while true do
            table.insert(share, 1)
            share.shr = {}
            print("this is thr, share len: ", #share, "manb: ", mantb.a, "tableaddr: ", share, "inneraddr: ", share.shr)
            mantb.a = mantb.a + 1
            effi.yield()
        end
    end)()
end)

coroutine.resume(co)

while true do
    table.insert(share, 1)
    print("this is main, share len: ", #share, "manb: ", mantb.a, "tableaddr: ", share, "inneraddr: ", share.shr or -1)
    thr:pause()
    effi.sleep(1)
    thr:resume()
end
