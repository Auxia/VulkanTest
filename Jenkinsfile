pipeline {
    agent any
    stages {
        stage('CMake Build') {
            steps {
                // This step will use the cmake plugin to configure and build
                cmakeBuild(
                    installation: 'cmake', // or set the name you configured in Jenkins Global Tool Configuration
                    generator: 'Unix Makefiles',  // or 'Ninja' if you use ninja
                    buildDir: 'build',
                    sourceDir: '.',               // Path to your top-level CMakeLists.txt
                    buildType: 'Release',         // or 'Debug' or whatever you prefer
                    steps: [
                        [args: 'all']             // What to build: 'all', 'install', etc.
                    ]
                )
            }
        }
    }
}
