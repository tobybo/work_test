local tab = {2,1,3}
local tab1 = {2,2,2}
table.sort(tab, function(ta, tb) return ta <= tb end)
print("done1")
table.sort(tab1, function(ta, tb) return ta <= tb end)
print("done2")
