#include "Application.h"

Application::Application() = default;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

void Application::runApp() {
    VideoPlayer player;
    player.initializeVideoCapture();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lane Road Detection", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    bool isPlaying = false;

    GLuint img = 0;
    int sizeX = 0;
    int sizeY = 0;

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBackground;
            const ImGuiViewport *viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::Begin("DockSpace Demo", nullptr, window_flags);
            ImGui::PopStyleVar(3);
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
            ImGui::End();
        }

        /* **** APPLICATION **** */

        RoadDetection detection;

        if (isPlaying) {
            cv::Mat frame = player.getFrame();
            if (frame.rows == 0) {
                player.nextVideo();
                frame = player.getFrame();
            }

            cv::Mat image = frame.clone();
            bool isDay = detection.isDayTime(image);
            cv::Mat filteredImg = detection.filterColors(image, isDay);
            cv::Mat gray = detection.applyGrayscale(filteredImg);
            cv::Mat blur = detection.applyGaussianBlur(gray);
            cv::Mat edges = detection.applyCanny(blur);
            cv::Mat maskedImg = detection.regionOfInterest(edges);
            std::vector<cv::Vec4i> linesP = detection.houghLines(maskedImg, image.clone(), false);
            frame = detection.drawLanes(image, linesP);

            cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
            if (img != 0) { glDeleteTextures(1, &img); }
            glGenTextures(1, &img);
            glBindTexture(GL_TEXTURE_2D, img);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, frame.cols, frame.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, frame.data);
            sizeX = frame.cols;
            sizeY = frame.rows;
        }

        ImGui::Begin("Video");
        ImVec2 size = ImGui::GetContentRegionAvail();
        ImVec2 imageSize = ImVec2(sizeX, sizeY);
        ImVec2 pos = ImVec2((size.x - imageSize.x) / 2, (size.y - imageSize.y) / 2 + 24);

        ImGui::SetCursorPos(pos);
        ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(img)), ImVec2(sizeX, sizeY));
        ImGui::End();


        /* Controls */
        ImGui::Begin("Controls");

        //ImGui::Button(!isPlaying ? "red" : "green")

        ImGui::PushStyleColor(ImGuiCol_Button, !isPlaying ? ImVec4(0, 1, 0, 1) : ImVec4(1, 0, 0, 1));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, !isPlaying ? ImVec4(0, 1, 0, 1) : ImVec4(1, 0, 0, 1));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, !isPlaying ? ImVec4(0, 1, 0, 1) : ImVec4(1, 0, 0, 1));
        ImVec2 sizeStartStop = ImGui::GetContentRegionAvail();
        if (ImGui::Button(!isPlaying ? "start" : "stop", ImVec2(sizeStartStop.x, sizeStartStop.x))) {
            isPlaying = !isPlaying;
        }
        ImGui::PopStyleColor(3);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 0.55, 0, 1));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1, 0.55, 0, 1));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1, 0.55, 0, 1));
        ImVec2 sizeRestart = ImGui::GetContentRegionAvail();
        if (ImGui::Button("restart", ImVec2(sizeRestart.x, sizeRestart.x))) {
            player.previousVideo();
            player.nextVideo();
        }
        ImGui::PopStyleColor(3);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5, 0.5, 0.5, 1));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.5, 0.5, 0.5, 1));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.5, 0.5, 0.5, 1));
        ImVec2 sizeLeft = ImGui::GetContentRegionAvail();

        if (ImGui::Button("previous", ImVec2(sizeLeft.x / 2 - ImGui::GetStyle().FramePadding.x,
                                             sizeLeft.x / 2 - ImGui::GetStyle().FramePadding.x))) {
            player.previousVideo();
        };

        ImGui::SameLine();

        ImVec2 sizeRight = ImGui::GetContentRegionAvail();
        if (ImGui::Button("next", ImVec2(sizeRight.x, sizeRight.x))) {
            player.nextVideo();
        };
        ImGui::PopStyleColor(3);

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        ImGui::EndFrame();

        glfwSwapBuffers(window);
        glfwPollEvents();

        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        /* **** APPLICATION **** */
    }

    glfwTerminate();
}


void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
