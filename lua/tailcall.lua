function test(i)
    if i%1000000==0 then
        print(i)
    end
    i=i+1
    return (test(i))
end
test(1)
