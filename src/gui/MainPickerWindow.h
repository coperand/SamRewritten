#pragma once
#include "../types/Achievement.h"
#include "../types/Game.h"
#include "AsyncGuiLoader.h"
#include "AchievementBoxRow.h"
#include "StatBoxRow.h"
#include "InputAppidBoxRow.h"
#include "AppBoxRow.h"

#include <vector>
#include <gtkmm-3.0/gtkmm/applicationwindow.h>
#include <gtkmm-3.0/gtkmm/listbox.h>
#include <gtkmm-3.0/gtkmm/builder.h>
#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/searchentry.h>
#include <gtkmm-3.0/gtkmm/scrolledwindow.h>
#include <gtkmm-3.0/gtkmm/notebook.h>
#include <gtkmm-3.0/gtkmm/modelbutton.h>
#include <gtkmm-3.0/gtkmm/aboutdialog.h>
#include <gtkmm-3.0/gtkmm/stack.h>
#include <gtkmm-3.0/gtkmm/spinbutton.h>
#include <gtkmm-3.0/gtkmm/combobox.h>
#include <gtkmm-3.0/gtkmm/radiobutton.h>
#include <gtkmm-3.0/gtkmm/separator.h>

/**
 * The main GUI class to display both the games ans the achievements to the user
 */
class MainPickerWindow : public Gtk::ApplicationWindow {
public:
    /**
     * Regular GtkMM constructor
     * https://developer.gnome.org/gtkmm-tutorial/stable/sec-builder-using-derived-widgets.html
     */
    MainPickerWindow(GtkApplicationWindow* cobject, const Glib::RefPtr<Gtk::Builder>& builder, AppId_t initial_app_id);
    virtual ~MainPickerWindow();

    /**
     * Empty the game list, leaving only the placeholder widget,
     * which means the loading widget.
     */
    void reset_game_list();

    /**
     * Empty the achievements list, leaving only the placeholder widget,
     * which means the loading widget.
     */
    void reset_achievement_list();

    /**
     * Empty the stats list, leaving only the placeholder widget,
     * which means the loading widget.
     */
    void reset_stat_list();

    /**
     * Adds a game to the game list. The new item will be added and saved,
     * but not drawn.
     */
    void add_to_game_list(const Game_t& app);

    /**
     * Adds an achievement to the achievement list. The new item will be added 
     * and saved, but not drawn.
     */
    void add_to_achievement_list(const Achievement_t& achievement);

    /**
     * Adds stat to the stat list. The new item will be added 
     * and saved, but not drawn.
     */
    void add_to_stat_list(const StatValue_t& stat);

    /**
     * Shows all widget that has been added to the list, removes all
     * the deleted entries from the GUI list.
     */
    void confirm_game_list();

    /**
     * Shows all widget that has been added to the list, removes all
     * the deleted entries from the GUI list.
     */
    void confirm_achievement_list();

    /**
     * Shows all widget that has been added to the list, removes all
     * the deleted entries from the GUI list.
     */
    void confirm_stat_list();

    /**
     * When a game is added to the list, the "missing icon" is used by default
     * Once the correct icon has been retrieved, this method will be called
     * to set the right image retrieved from Steam
     */
    void refresh_app_icon(AppId_t app_id);

    /**
     * Same as above for each achievement
     */
    void refresh_achievement_icon(AppId_t app_id, std::string id);

    /**
     * Set the game_list placeholder to the no games found placeholder
     * and show it
     */
    void show_fetch_games_placeholder();

    /**
     * Set the game_list placeholder to the fetching games placeholder
     * and show it
     */
    void show_no_games_found_placeholder();

    /**
     * Set the achievement_list placeholder to the no achievements found placeholder
     * and show it
     */
    void show_fetch_achievements_placeholder();

    /**
     * Set the stat_list placeholder to the no stat found placeholder
     * and show it
     */
    void show_fetch_stats_placeholder();

    /**
     * Set the game_list placeholder to the fetching achievements placeholder
     * and show it
     */
    void show_no_achievements_found_placeholder();

    /**
     * Set the stat_list placeholder to the fetching stats placeholder
     * and show it
     */
    void show_no_stats_found_placeholder();
private:
    // Gtk Callbacks
    void on_game_search_changed();
    void on_achievement_search_changed();
    void on_stat_search_changed();
    void on_page_switched(Widget* page, guint page_number);
    void on_game_row_activated(Gtk::ListBoxRow* row);
    void on_refresh_games_button_clicked();
    void on_refresh_achievements_button_clicked();
    void on_back_button_clicked();
    void on_store_button_clicked();
    void on_invert_all_achievements_button_clicked();
    void on_start_timed_modifications_button_clicked();
    void on_lock_all_achievements_button_clicked();
    void on_unlock_all_achievements_button_clicked();
    void on_about_button_clicked();
    void on_close_about_dialog(int response_id);
    void on_cancel_timed_modifications_button_clicked();
    bool on_close_timed_modifications_window(GdkEventAny* evt);
    void on_submit_timed_modifications_button_clicked();
    bool on_timer_expire();
    void schedule_timer();

    bool on_delete(GdkEventAny* evt);

    // Private Methods
    void switch_to_achievement_page();
    void switch_to_games_page();

    // Member variables
    Glib::RefPtr<Gtk::Builder> m_builder;
    Gtk::AboutDialog *m_about_dialog;
    Gtk::Button *m_back_button;
    Gtk::Button *m_store_button;
    Gtk::Button *m_refresh_games_button;
    Gtk::ModelButton *m_about_button;
    Gtk::ModelButton *m_refresh_achievements_button;
    Gtk::Separator *m_separator_lock;
    Gtk::ModelButton *m_unlock_all_achievements_button;
    Gtk::ModelButton *m_lock_all_achievements_button;
    Gtk::ModelButton *m_invert_all_achievements_button;
    Gtk::Separator *m_separator_display;
    // Currently these are checkbuttons and don't close the popover
    // when they're clicked. That might be desirable.
    // They could be made to be Gtk::ModelButton's like the other
    // ones with role of Gtk::BUTTON_ROLE_CHECK, but that behaves
    // approximately the same way and doesn't close the popover
    Gtk::CheckButton *m_display_only_locked_button;
    Gtk::CheckButton *m_display_only_unlocked_button;
    Gtk::Separator *m_separator_timed;
    Gtk::ModelButton *m_start_timed_modifications_button;
    Gtk::ListBox *m_game_list;
    Gtk::ListBox *m_achievement_list;
    Gtk::ListBox *m_stat_list;
    Gtk::Stack *m_main_stack;
    Gtk::SearchEntry *m_game_search_bar;
    Gtk::SearchEntry *m_achievement_search_bar;
    Gtk::SearchEntry *m_stat_search_bar;
    Gtk::ScrolledWindow *m_game_list_view;
    Gtk::Notebook *m_achievement_and_stat_notebook;
    Gtk::Box *m_fetch_games_placeholder;
    Gtk::Box *m_no_games_found_placeholder;
    Gtk::Box *m_fetch_achievements_placeholder;
    Gtk::Box *m_fetch_stats_placeholder;
    Gtk::Box *m_no_achievements_found_placeholder;
    Gtk::Box *m_no_stats_found_placeholder;

    Gtk::Window *m_timed_modifications_window;
    Gtk::SpinButton* m_modifications_time_amount;
    Gtk::ComboBox* m_modifications_time_unit;
    // Since GTK doesn't offer an easy way to get the active
    // button (https://gitlab.gnome.org/GNOME/gtk/issues/243)
    // it's simpler to just store off the few we need..
    Gtk::RadioButton* m_even_spacing_button;
    Gtk::RadioButton* m_random_spacing_button;
    Gtk::RadioButton* m_order_of_selection_button;
    Gtk::RadioButton* m_order_random_button;
    Gtk::CheckButton* m_exit_game_after_done_button;
    Gtk::Label* m_applying_modifications_label;
    Gtk::Button* m_submit_timed_modifications_button;

    InputAppidBoxRow m_input_appid_row;
    AppId_t m_initial_app_id;

    std::vector<AppBoxRow*> m_app_list_rows;
    std::vector<AchievementBoxRow*> m_achievement_list_rows;
    std::vector<StatBoxRow*> m_stat_list_rows;
    AsyncGuiLoader m_async_loader;

    sigc::connection m_timed_modifications_timer;
    std::vector<uint64_t> m_timed_modification_times;
};
