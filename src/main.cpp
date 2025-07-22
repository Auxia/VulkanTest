#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <memory>

#include <vulkan/vulkan_raii.hpp>

#include <vulkan/vk_platform.h>

#define GLFW_INCLUDE_VULKAN // REQUIRED only for GLFW CreateWindowSurface.
#include <GLFW/glfw3.h>

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;

class HelloTriangleApplication {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow* window = nullptr;

    vk::raii::Context  context;
    vk::raii::Instance instance = nullptr;

    void initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, "VulkanTest", nullptr, nullptr);
    }

    void initVulkan() {
        createInstance();
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        glfwDestroyWindow(window);

        glfwTerminate();
    }

    void createInstance() {
        constexpr auto appInfo = vk::ApplicationInfo("Hello Triangle",
                                                    1, "No Engine", 1,
                                                    vk::ApiVersion14);

        // Get the required instance extensions from GLFW.
        uint32_t glfwExtensionCount = 0;
        auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        uint32_t enabledExtensionCount = glfwExtensionCount + 2; // MacOS Specific -> 2
        const char** ppEnabledExtensionNames = (const char**)malloc(enabledExtensionCount * sizeof(char*));

        uint32_t offset = 0;
        for (; offset < glfwExtensionCount; ++offset) {
            ppEnabledExtensionNames[offset] = glfwExtensions[offset];
        }
        ppEnabledExtensionNames[offset++] = VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME;
        ppEnabledExtensionNames[offset++] = VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME;

        printEnabledExtensions();

        vk::InstanceCreateInfo createInfo = vk::InstanceCreateInfo (
            vk::InstanceCreateFlags() | vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR,
            &appInfo, 
            {}, {},
            enabledExtensionCount, ppEnabledExtensionNames);
        instance = vk::raii::Instance(context, createInfo);
    }

    void printEnabledExtensions() {
        auto extensions = context.enumerateInstanceExtensionProperties();
        std::cout << "Available Extensions:\n";
        for  (const auto& extension : extensions) {
            std::cout << '\t' << extension.extensionName << '\n';
        }
    }
};

int main() {
    try {
        HelloTriangleApplication app;
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}