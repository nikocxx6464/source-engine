export ICON=mod_icon.png
export PACKAGE=hl2chaos
export APP_NAME="Half-Life 2: Chaos"
cd srceng-mod-launcher
git clone https://gitlab.com/LostGamer/android-sdk
export ANDROID_SDK_HOME=$PWD/android-sdk
git pull
chmod +x android/script.sh
./android/scripts/script.sh
chmod +x waf
./waf configure -T release &&
./waf build
