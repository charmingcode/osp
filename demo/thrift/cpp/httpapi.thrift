namespace cpp HttpApi

service HttpApi {
      bool   setKeyVal(1:string key, 2:string val),
      string getValByKey(1:string key)
}
