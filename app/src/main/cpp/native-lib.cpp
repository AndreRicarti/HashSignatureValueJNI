#include <jni.h>
#include <string>

extern "C"
jstring
Java_com_example_aricarti_hashcode_MainActivity_stringFromJNI(JNIEnv* env,  jobject thiz){

    jclass native_clazz = env->GetObjectClass(thiz);

    // Obter os métodos ID getPackageManager
    jmethodID methodID_func =env->GetMethodID(native_clazz,"getPackageManager", "()Landroid/content/pm/PackageManager;");

    // Obter o gerente pacote de aplicativos
    jobject package_manager = env->CallObjectMethod(thiz, methodID_func);

    // Obter classe PackageManager
    jclass pm_clazz = env->GetObjectClass(package_manager);

    // Obter getPackageInfo processo ID
    jmethodID methodID_pm = env->GetMethodID( pm_clazz,
                                              "getPackageInfo", "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");

    // Obter o nome do pacote
    jmethodID methodID_packagename =env->GetMethodID(native_clazz,"getPackageName", "()Ljava/lang/String;");
    jstring name_str = static_cast<jstring>(env->CallObjectMethod(thiz, methodID_packagename));


    // Obter informações do pacote de aplicativos
    jobject package_info = env->CallObjectMethod(package_manager,
                                                 methodID_pm, name_str, 64);//env->NewStringUTF("com.example.contasdf")

    // Obter classe PackageInfo
    jclass pi_clazz = env->GetObjectClass( package_info);

    // Obter a assinatura matriz de propriedade ID
    jfieldID fieldID_signatures = env->GetFieldID( pi_clazz,
                                                   "signatures", "[Landroid/content/pm/Signature;");

    // Obter um conjunto de assinatura, a ser modificado
    jobject signatur = env->GetObjectField(package_info, fieldID_signatures);
    jobjectArray  signatures = reinterpret_cast<jobjectArray>(signatur);
    // Obter assinaturas
    jobject signature = env->GetObjectArrayElement(signatures, 0);

    // Obter a classe Signature, a ser modificado
    jclass s_clazz = env->GetObjectClass(signature);

    // Obter o ID método hashCode
    jmethodID methodID_hc = env->GetMethodID(s_clazz, "hashCode", "()I");

    // Obter o gerenciador de pacotes de aplicativos, a ser modificado
    int hash_code = env->CallIntMethod(signature, methodID_hc);

    char str[100];

    sprintf(str, "%u", hash_code);
    return env->NewStringUTF(str);

}
