#pragma once
#include <QString>

inline QString appStyleSheet() {
    return R"(
        * { font-family: 'Segoe UI', 'Inter', 'Helvetica Neue', Arial, sans-serif; font-size: 13px; color: #1F2937; }
        QMainWindow, QDialog { background: #F3F4F6; }

        /* Header */
        QFrame#header {
            border-radius: 16px;
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #4F46E5, stop:1 #9333EA);
        }
        QLabel#title { color: white; font-size: 22px; font-weight: 700; }
        QLabel#subtitle { color: #E0E7FF; font-size: 12px; }
        QLabel#dayPill {
            color: white; font-weight: 700; font-size: 14px;
            background: rgba(255,255,255,0.20); border-radius: 14px; padding: 6px 16px;
        }

        /* Statistics */
        QFrame#card { background: white; border-radius: 14px; border: 1px solid #E5E7EB; }
        QLabel#statValue { font-size: 24px; font-weight: 700; }
        QLabel#statCaption { color: #6B7280; font-size: 12px; }
        QLabel#statIcon { font-size: 22px; }

        /* Panels */
        QFrame#panel { background: white; border-radius: 14px; border: 1px solid #E5E7EB; }
        QLabel#panelTitle { font-size: 15px; font-weight: 700; color: #111827; }

        /* Search */
        QLineEdit {
            background: white; border: 1px solid #D1D5DB; border-radius: 10px; padding: 8px 12px;
            selection-background-color: #C7D2FE;
        }
        QLineEdit:focus { border: 2px solid #6366F1; padding: 7px 11px; }

        /* Tables */
        QTableWidget {
            background: white; alternate-background-color: #F9FAFB; border: none;
            gridline-color: transparent; selection-background-color: #E0E7FF; selection-color: #1E1B4B;
        }
        QTableWidget::item { padding: 6px; border-bottom: 1px solid #F3F4F6; }
        QHeaderView { background: #F9FAFB; border: none; }
        QTableCornerButton::section { background: #F9FAFB; border: none; }
        QHeaderView::section {
            background: #F9FAFB; color: #6B7280; font-weight: 700; padding: 8px;
            border: none; border-bottom: 2px solid #E5E7EB;
        }

        /* Buttons */
        QPushButton {
            border: none; border-radius: 10px; padding: 9px 16px; font-weight: 600; color: white;
        }
        QPushButton[role="primary"] { background: #4F46E5; }
        QPushButton[role="primary"]:hover { background: #4338CA; }
        QPushButton[role="secondary"] { background: white; color: #4F46E5; border: 1px solid #C7D2FE; }
        QPushButton[role="secondary"]:hover { background: #EEF2FF; }
        QPushButton[role="success"] { background: #10B981; }
        QPushButton[role="success"]:hover { background: #059669; }
        QPushButton[role="warning"] { background: #F59E0B; }
        QPushButton[role="warning"]:hover { background: #D97706; }
        QPushButton[role="ghost"] { background: rgba(255,255,255,0.18); }
        QPushButton[role="ghost"]:hover { background: rgba(255,255,255,0.32); }
        QPushButton:pressed { padding-top: 10px; padding-bottom: 8px; }

        /* Log */
        QPlainTextEdit {
            background: #111827; color: #A7F3D0; border-radius: 12px; padding: 8px;
            font-family: 'Consolas', 'Fira Code', monospace; font-size: 12px;
        }

        /* Dialog controls */
        QComboBox { background: white; border: 1px solid #D1D5DB; border-radius: 10px; padding: 7px 12px; }
        QComboBox:focus { border: 2px solid #6366F1; }
        QComboBox QAbstractItemView { background: white; selection-background-color: #E0E7FF; selection-color: #1E1B4B; }
        QDialogButtonBox QPushButton { background: #4F46E5; min-width: 70px; }
        QMessageBox { background: white; }
        QScrollBar:vertical { background: transparent; width: 10px; }
        QScrollBar::handle:vertical { background: #D1D5DB; border-radius: 5px; min-height: 30px; }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0; }
    )";
}
