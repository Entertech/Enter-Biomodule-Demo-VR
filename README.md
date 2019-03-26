# Enter-Biomodule-Demo-VR

**运行说明**

这是一个Unity工程，运行该项目，需先转为Android工程，并将该工程作为一个Android Module导入到Android Studio，并且需要在该module的gradle文件中添加如下依赖：

```groovy
implementation files('libs/unity-classes.jar')
implementation "com.polidea.rxandroidble2:rxandroidble:1.8.0"
implementation 'com.orhanobut:logger:1.15'
implementation 'cn.entertech:flowtimeble:1.0.3'
```

