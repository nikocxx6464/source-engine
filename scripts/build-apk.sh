export ICON=lc.png
export PACKAGE=snowdrop_escape
export APP_NAME="Snowdrop Escape"
cd srceng-mod-launcher
git clone https://github.com/ItzVladik/android-sdk
export ANDROID_SDK_HOME=$PWD/android-sdk
git pull
chmod +x android/scripts/script.sh
./android/scripts/script.sh
chmod +x waf
./waf configure -T release --javac-source-target=8 &&
./waf build
