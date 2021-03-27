#ifndef OLED_MONITOR
  #define OLED_MONITOR
    class OledMonitor
    {
        public:
            OledMonitor();
            void setup();
            void render();
            void set_iso(int iso);
            void set_top_av(int top_av);
            void set_top_t(int top_t);
            void set_main_av(int main_av);
            void set_main_t(int main_t);
            void set_bottom_av(int bottom_av);
            void set_bottom_t(int bottom_t);
            void set_ev(float ev);
            void set_status_str(char status_str);
        private:
            char _iso_str[9];
            char _top_av_str[4];
            char _top_t_str[4];
            char _main_av_str[4];
            char _main_t_str[4];
            char _bottom_av_str[4];
            char _bottom_t_str[4];
            char _ev_str[9];
            char _status_str[2];
    };

#endif
