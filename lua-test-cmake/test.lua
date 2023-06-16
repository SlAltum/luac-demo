-- package.cpath = "luaclib/?.so"

function Init(args)
    print("call [init] function", args)
end

function Loop()
    print("call [loop] function")
    for k, v in ipairs({1,2,3,4,5}) do
        print("value = " .. v)
    end
end

function Release()
    print("call [release] function")
end