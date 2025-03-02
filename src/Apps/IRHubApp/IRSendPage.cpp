#include "Apps/IRHubApp/IRHubAllPages.h"

namespace Apps::IRHub::Pages
{
    IRSendPage::~IRSendPage() { _window->is_active = true; }

    IRSendPage::IRSendPage(Window *window) : _window(window) {}

    void IRSendPage::open()
    {
        // _window->add_widget(new UIButton(40, 35, "Search", std::bind(&IRSendPage::btn_start_search, this)));
        // _window->add_widget(new UIButton(40, 50, "Back", std::bind(&Window::open_page<MainMenuPage>, _window), ST7735_RED));
        _window->is_active = false;
        _file_explorer.start(IR_FILES_FOLDER_PATH);
    }

    void IRSendPage::update()
    {
        const char *path = _file_explorer.loop();
        if (path != nullptr)
        {
            uint16_t buff_len = Managers::SDManager::get_file_size(path) / sizeof(uint16_t);
            char *ir_buff = Managers::SDManager::read_file(path);
            delete[] path;
            for (uint8_t i = 0; i < buff_len; i++)
                Serial.printf("%d, ", (uint16_t)ir_buff[i]);
            IRSender::send_raw((uint16_t *)ir_buff, buff_len);
            delete[] ir_buff;
        }
    }

    // void IRSendPage::btn_start_search()
    // {
    // }
}