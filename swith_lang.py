import time
import string
import os
from pynput.keyboard import Key, Controller
from AppKit import NSWorkspace, NSLocale


def get_active_window_name():
    app_name = NSWorkspace.sharedWorkspace().activeApplication()['NSApplicationName']
    print(app_name)
    return app_name


def get_input_lang():
    cmd = 'defaults read ~/Library/Preferences/com.apple.HIToolbox.plist AppleSelectedInputSources|grep "KeyboardLayout Name"'
    out = os.popen(cmd).read().strip()
    parsed_out = ''.join([x for x in out if x not in string.punctuation])
    lang = parsed_out.split(' ')[-1]
    return lang


def press_ctrl_space(number_of_switches):
    keyboard.press(Key.ctrl)   # Натискає Ctrl
    for i in range(0, number_of_switches):
        keyboard.press(Key.space)  # Натискає Space
        time.sleep(0.2)
        keyboard.release(Key.space)  # Відпускає Space
        time.sleep(0.2)
    keyboard.release(Key.ctrl)   # Відпускає Ctrl


def switch_input_source(input_source_name):
    # Get the list of input sources
    input_sources = NSWorkspace.sharedWorkspace().inputSources()
    # https://developer.apple.com/documentation/appkit/nsevent

    # Find the input source with the specified name
    for source in input_sources:
        if source['name'] == input_source_name:
            # Activate the input source
            NSWorkspace.sharedWorkspace().selectInputSource(source)
            return True
    return False

keyboard = Controller()


number_of_switches = 1
while True:
    time.sleep(1)
    cur_lang = get_input_lang()
    print(cur_lang)

    if cur_lang == 'ABC':
        break

    press_ctrl_space(number_of_switches)

    number_of_switches += 1

