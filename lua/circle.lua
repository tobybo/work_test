gActions = {1}
while next(gActions) do
    table.remove(gActions, 1)
    table.insert(gActions, 1)
end

