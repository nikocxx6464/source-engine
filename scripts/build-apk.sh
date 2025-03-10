export ICON=swelter.png
export PACKAGE=swelter
export APP_NAME="Swelter"
cd srceng-mod-launcher
git clone https://github.com/ItzVladik/android-sdk
export ANDROID_SDK_HOME=$PWD/android-sdk
git pull
chmod +x android/scripts/script.sh
./android/scripts/script.sh
chmod +x waf
./waf configure -T release --javac-source-target=8 &&
./waf build
