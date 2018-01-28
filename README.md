## Development setup

1.  Download [openFrameworks][1].

2.  Download the following addons and install them by copying them to `openFrameworks/addons`:
    - [ofxEtherdream][2]
    - [ofxIlda][3]

3.  Create a new project using your platform's project generator ([instructions here][4]). When creating the project, include the addons ofxEtherdream, ofxIlda, and ofxOsc (the ofxOsc addon comes with the openFrameworks download).

4.  Navigate to the project directory.

5.  Delete the `src` directory that openFrameworks created for you.

6.  Grab the git repository. I think this will work.

    ```
    git init
    git remote add origin git@github.com:alexdmiller/cone.git
    git pull
    ```

7.  Edit `.gitignore` and add any project configuration files that the project generator added for you.

8.  Compile and run.

## Keyboard shortcuts

- `p`: Projector calibration mode
- `l`: Laser calibration mode
- `d`: Demo animation mode
- `space`: Run generators and listen for OSC messages

[1]: http://openframeworks.cc/
[2]: https://github.com/memo/ofxEtherdream
[3]: https://github.com/memo/ofxIlda
[4]: http://openframeworks.cc/download/
