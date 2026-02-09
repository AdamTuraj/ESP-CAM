// Video streaming example using ESP32-CAM. Code taken from https://docs.cirkitdesigner.com/component/b03da137-6105-4f5a-a6f4-6983b68cc78f/esp-cam-ov2640

#include <WiFi.h>
#include <esp_camera.h>

// Replace with your Wi-Fi credentials
const char *ssid = "Your_SSID";
const char *password = "Your_PASSWORD";

// Camera configuration
#define PWDN_GPIO_NUM -1
#define RESET_GPIO_NUM 40
#define XCLK_GPIO_NUM 37
#define SIOD_GPIO_NUM 42
#define SIOC_GPIO_NUM 41
#define Y9_GPIO_NUM 36
#define Y8_GPIO_NUM 48
#define Y7_GPIO_NUM 21
#define Y6_GPIO_NUM 13
#define Y5_GPIO_NUM 14
#define Y4_GPIO_NUM 47
#define Y3_GPIO_NUM 12
#define Y2_GPIO_NUM 11
#define VSYNC_GPIO_NUM 39
#define HREF_GPIO_NUM 38
#define PCLK_GPIO_NUM 35

void setup()
{
    Serial.begin(115200);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWi-Fi connected");

    // Initialize the camera
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    if (esp_camera_init(&config) != ESP_OK)
    {
        Serial.println("Camera initialization failed");
        return;
    }
    Serial.println("Camera initialized successfully");
}

void loop()
{
    // Capture an image
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb)
    {
        Serial.println("Failed to capture image");
        return;
    }

    // Print image size
    Serial.printf("Captured image size: %d bytes\n", fb->len);

    // Return the frame buffer to the driver
    esp_camera_fb_return(fb);

    delay(5000); // Wait 5 seconds before capturing the next image
}