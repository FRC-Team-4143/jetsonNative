plugins {
    id "cpp"
    id "google-test-test-suite"
    id "edu.wpi.first.GradleRIO" version "2024.1.1-beta-2"
}

// Simulation configuration (e.g. environment variables).
wpi.sim.addGui().defaultEnabled = true
wpi.sim.addDriverstation()

model {
    components {
        frcUserProgram(NativeExecutableSpec) {
            targetPlatform wpi.platforms.desktop

            sources.cpp {
                source {
                    srcDir 'src/main/cpp'
                    include '**/*.cpp', '**/*.cc'
                }
                exportedHeaders {
                    srcDir 'src/main/include'
                }
            }

            wpi.cpp.enableExternalTasks(it)

            wpi.sim.enable(it)

            // Defining my dependencies. In this case, WPILib (+ friends), and vendor libraries.
            wpi.cpp.vendor.cpp(it)
            wpi.cpp.deps.wpilib(it)
        }
    }
}
