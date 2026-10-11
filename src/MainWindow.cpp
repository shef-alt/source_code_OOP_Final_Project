#include <QBrush>
#include <QColor>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include "MainWindow.h"
#include "Style.h"

static QString money(double value) {
    return "Rp " + QString::number(value, 'f', 0);
}

static QTableWidget* makeTable(QStringList headers) {
    QTableWidget *table = new QTableWidget(0, headers.size());
    table->setHorizontalHeaderLabels(headers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setAlternatingRowColors(true);
    table->setShowGrid(false);
    table->setFocusPolicy(Qt::NoFocus);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(headers.size() - 1, QHeaderView::Stretch);
    table->horizontalHeader()->setHighlightSections(false);
    table->verticalHeader()->setVisible(false);
    table->verticalHeader()->setDefaultSectionSize(38);
    return table;
}

static QPushButton* makeButton(QString text, const char *role) {
    QPushButton *button = new QPushButton(text);
    button->setProperty("role", role);
    button->setCursor(Qt::PointingHandCursor);
    return button;
}

static QFrame* makePanel(QString title, QWidget *content) {
    QFrame *panel = new QFrame;
    panel->setObjectName("panel");
    QVBoxLayout *layout = new QVBoxLayout(panel);
    layout->setContentsMargins(16, 14, 16, 14);
    QLabel *label = new QLabel(title);
    label->setObjectName("panelTitle");
    layout->addWidget(label);
    layout->addWidget(content);
    return panel;
}

static void addShadow(QWidget *widget) {
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(widget);
    shadow->setBlurRadius(18);
    shadow->setOffset(0, 3);
    shadow->setColor(QColor(0, 0, 0, 30));
    widget->setGraphicsEffect(shadow);
}

static QTableWidgetItem* makeCell(QString text, Qt::Alignment align = Qt::AlignVCenter | Qt::AlignLeft) {
    QTableWidgetItem *cell = new QTableWidgetItem(text);
    cell->setTextAlignment(align);
    return cell;
}

static void colorCell(QTableWidgetItem *cell, QString textColor, QString backColor) {
    cell->setForeground(QBrush(QColor(textColor)));
    cell->setBackground(QBrush(QColor(backColor)));
}

// MainWindow
QWidget* MainWindow::makeStatCard(QString icon, QString caption, QString color, QLabel *&valueLabel) {
    QFrame *card = new QFrame;
    card->setObjectName("card");
    QHBoxLayout *row = new QHBoxLayout(card);
    row->setContentsMargins(16, 12, 16, 12);

    QLabel *iconLabel = new QLabel(icon);
    iconLabel->setObjectName("statIcon");
    iconLabel->setFixedSize(44, 44);
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setStyleSheet(QString("QLabel#statIcon { background: %1; border-radius: 12px; }").arg(color));

    QVBoxLayout *column = new QVBoxLayout;
    column->setSpacing(0);
    valueLabel = new QLabel("0");
    valueLabel->setObjectName("statValue");
    QLabel *captionLabel = new QLabel(caption);
    captionLabel->setObjectName("statCaption");
    column->addWidget(valueLabel);
    column->addWidget(captionLabel);

    row->addWidget(iconLabel);
    row->addLayout(column, 1);
    addShadow(card);
    return card;
}

MainWindow::MainWindow() {
    setWindowTitle("Library Management System");
    resize(1200, 760);
    setStyleSheet(appStyleSheet());
    library.seedSampleData();

    QWidget *central = new QWidget;
    QVBoxLayout *root = new QVBoxLayout(central);
    root->setContentsMargins(20, 20, 20, 20);
    root->setSpacing(14);

    // Header
    QFrame *header = new QFrame;
    header->setObjectName("header");
    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(24, 18, 24, 18);
    QVBoxLayout *titles = new QVBoxLayout;
    titles->setSpacing(2);
    QLabel *title = new QLabel(QString::fromUtf8("📚  Library Management"));
    title->setObjectName("title");
    QLabel *subtitle = new QLabel("Encapsulation  •  Abstraction  •  Inheritance  •  Polymorphism");
    subtitle->setObjectName("subtitle");
    titles->addWidget(title);
    titles->addWidget(subtitle);
    dayLabel = new QLabel;
    dayLabel->setObjectName("dayPill");
    QPushButton *day1 = makeButton("+1 day", "ghost");
    QPushButton *day7 = makeButton("+7 days", "ghost");
    headerLayout->addLayout(titles, 1);
    headerLayout->addWidget(dayLabel);
    headerLayout->addSpacing(8);
    headerLayout->addWidget(day1);
    headerLayout->addWidget(day7);
    addShadow(header);
    root->addWidget(header);

    // Statistik
    QHBoxLayout *stats = new QHBoxLayout;
    stats->setSpacing(14);
    stats->addWidget(makeStatCard(QString::fromUtf8("📦"), "Total items", "#E0E7FF", totalLabel));
    stats->addWidget(makeStatCard(QString::fromUtf8("✅"), "Available", "#D1FAE5", availLabel));
    stats->addWidget(makeStatCard(QString::fromUtf8("📤"), "Borrowed", "#FEF3C7", borrowedLabel));
    stats->addWidget(makeStatCard(QString::fromUtf8("⏰"), "Overdue", "#FEE2E2", lateLabel));
    stats->addWidget(makeStatCard(QString::fromUtf8("💰"), "Unpaid fines", "#FCE7F3", finesLabel));
    root->addLayout(stats);

    // Tabel
    searchEdit = new QLineEdit;
    searchEdit->setPlaceholderText(QString::fromUtf8("Search title, type, or author..."));
    itemTable = makeTable({"ID", "Item", "Title", "Details", "Status"});
    memberTable = makeTable({"ID", "Member", "Role", "Loans", "Fines"});

    QWidget *itemContent = new QWidget;
    QVBoxLayout *itemLayout = new QVBoxLayout(itemContent);
    itemLayout->setContentsMargins(0, 0, 0, 0);
    itemLayout->addWidget(searchEdit);
    itemLayout->addWidget(itemTable);

    QFrame *itemPanel = makePanel("Collection", itemContent);
    QFrame *memberPanel = makePanel("Members", memberTable);
    QHBoxLayout *tables = new QHBoxLayout;
    tables->setSpacing(14);
    tables->addWidget(itemPanel, 3);
    tables->addWidget(memberPanel, 2);
    root->addLayout(tables, 1);

    // Tombol action
    QPushButton *addItem = makeButton(QString::fromUtf8("+ Add Item"), "secondary");
    QPushButton *addMember = makeButton(QString::fromUtf8("+  Add Member"), "secondary");
    QPushButton *borrow = makeButton(QString::fromUtf8("📤  Borrow"), "primary");
    QPushButton *giveBack = makeButton(QString::fromUtf8("📥  Return"), "success");
    QPushButton *pay = makeButton(QString::fromUtf8("💳  Pay Fines"), "warning");
    QHBoxLayout *actions = new QHBoxLayout;
    actions->setSpacing(10);
    actions->addWidget(addItem);
    actions->addWidget(addMember);
    actions->addStretch(1);
    actions->addWidget(borrow);
    actions->addWidget(giveBack);
    actions->addWidget(pay);
    root->addLayout(actions);

    logBox = new QPlainTextEdit;
    logBox->setReadOnly(true);
    logBox->setMaximumHeight(120);
    root->addWidget(logBox);
    setCentralWidget(central);

    connect(searchEdit, &QLineEdit::textChanged, this, &MainWindow::refresh);
    connect(day1, &QPushButton::clicked, this, [this] { onAdvance(1); });
    connect(day7, &QPushButton::clicked, this, [this] { onAdvance(7); });
    connect(addItem, &QPushButton::clicked, this, &MainWindow::onAddItem);
    connect(addMember, &QPushButton::clicked, this, &MainWindow::onAddMember);
    connect(borrow, &QPushButton::clicked, this, &MainWindow::onBorrow);
    connect(giveBack, &QPushButton::clicked, this, &MainWindow::onReturn);
    connect(pay, &QPushButton::clicked, this, &MainWindow::onPayFines);

    logMessage("Ready. Select a member and an item, then click Borrow.");
    refresh();
}

int MainWindow::selectedId(QTableWidget *table) {
    QModelIndexList rows = table->selectionModel()->selectedRows();
    if (rows.isEmpty()) return -1;
    return table->item(rows.first().row(), 0)->text().toInt();
}

void MainWindow::logMessage(QString msg) {
    logBox->appendPlainText(QString("[Day %1]  %2").arg(library.getToday()).arg(msg));
}

void MainWindow::showError(string error) {
    QString text = QString::fromStdString(error);
    QMessageBox::warning(this, "Action rejected", text);
    logMessage("Rejected: " + text);
}

QString MainWindow::memberName(int memberId) {
    const Member *member = library.getMember(memberId);
    if (member == nullptr) return "?";
    return QString::fromStdString(member->getName());
}

void MainWindow::refresh() {
    dayLabel->setText(QString::fromUtf8("📅  Day %1").arg(library.getToday()));

    int selectedItem = selectedId(itemTable);
    int selectedMember = selectedId(memberTable);
    int today = library.getToday();

    // Statistik 
    int total = 0, available = 0, late = 0;
    for (const LibraryItem *item : library.itemList()) {
        total++;
        if (item->isAvailable()) available++;
        else if (item->daysLate(today) > 0) late++;
    }
    double fines = 0;
    for (const Member *member : library.memberList()) fines += member->getFines();
    totalLabel->setText(QString::number(total));
    availLabel->setText(QString::number(available));
    borrowedLabel->setText(QString::number(total - available));
    lateLabel->setText(QString::number(late));
    finesLabel->setText(money(fines));

    //Tabel item
    vector<const LibraryItem*> items = library.findItems(searchEdit->text().toStdString());
    itemTable->setRowCount(0);
    for (const LibraryItem *item : items) {  // pointer base class, sifat inheritence
        int row = itemTable->rowCount();
        itemTable->insertRow(row);

        QString status, textColor, backColor;
        if (item->isAvailable()) {
            status = QString::fromUtf8("●  Available");
            textColor = "#047857";
            backColor = "#D1FAE5";
        } else if (item->daysLate(today) > 0) {
            status = QString::fromUtf8("●  Overdue - %1 (due day %2)")
                         .arg(memberName(item->getBorrowerId())).arg(item->getDueDay());
            textColor = "#B91C1C";
            backColor = "#FEE2E2";
        } else {
            status = QString::fromUtf8("●  Borrowed - %1 (due day %2)")
                         .arg(memberName(item->getBorrowerId())).arg(item->getDueDay());
            textColor = "#B45309";
            backColor = "#FEF3C7";
        }

        itemTable->setItem(row, 0, makeCell(QString::number(item->getId()), Qt::AlignCenter));
        itemTable->setItem(row, 1, makeCell(QString::fromStdString(item->type())));
        itemTable->setItem(row, 2, makeCell(QString::fromStdString(item->getTitle())));
        itemTable->setItem(row, 3, makeCell(QString::fromStdString(item->details())));
        QTableWidgetItem *statusCell = makeCell(status);
        colorCell(statusCell, textColor, backColor);
        itemTable->setItem(row, 4, statusCell);
        if (item->getId() == selectedItem) itemTable->selectRow(row);
    }

    // Tabel member
    memberTable->setRowCount(0);
    for (const Member *member : library.memberList()) {
        int row = memberTable->rowCount();
        memberTable->insertRow(row);
        memberTable->setItem(row, 0, makeCell(QString::number(member->getId()), Qt::AlignCenter));
        memberTable->setItem(row, 1, makeCell(QString::fromStdString(member->getName())));
        memberTable->setItem(row, 2, makeCell(QString::fromStdString(member->role())));
        memberTable->setItem(row, 3, makeCell(QString("%1 / %2").arg(member->getLoans().size()).arg(member->maxLoans()),
                                              Qt::AlignCenter));
        QTableWidgetItem *fineCell = makeCell(money(member->getFines()));
        if (member->getFines() > 0) colorCell(fineCell, "#B91C1C", "#FEE2E2");
        else colorCell(fineCell, "#047857", "#D1FAE5");
        memberTable->setItem(row, 4, fineCell);
        if (member->getId() == selectedMember) memberTable->selectRow(row);
    }
}

void MainWindow::onAddItem() {
    QDialog dialog(this);
    dialog.setWindowTitle("Add Item");
    dialog.setMinimumWidth(380);
    QFormLayout *form = new QFormLayout(&dialog);
    form->setContentsMargins(20, 20, 20, 20);
    form->setSpacing(12);
    QComboBox *type = new QComboBox;
    type->addItems({"Book", "Magazine", "DVD"});
    QLineEdit *title = new QLineEdit;
    QLineEdit *detail = new QLineEdit;
    detail->setPlaceholderText("Author");
    connect(type, &QComboBox::currentTextChanged, &dialog, [detail](QString t) {
        if (t == "Book") detail->setPlaceholderText("Author");
        else if (t == "Magazine") detail->setPlaceholderText("Issue");
        else detail->setPlaceholderText("Duration (minutes)");
    });
    form->addRow("Type", type);
    form->addRow("Title", title);
    form->addRow("Author / Issue / Minutes", detail);
    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    form->addRow(buttons);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    if (dialog.exec() != QDialog::Accepted) return;

    string error;
    int id = library.addItem(type->currentText().toStdString(),
                             title->text().trimmed().toStdString(),
                             detail->text().trimmed().toStdString(), error);
    if (id < 0) {
        showError(error);
        return;
    }
    logMessage(QString("Added %1 #%2: %3").arg(type->currentText()).arg(id).arg(title->text()));
    refresh();
}

void MainWindow::onAddMember() {
    QDialog dialog(this);
    dialog.setWindowTitle("Add Member");
    dialog.setMinimumWidth(360);
    QFormLayout *form = new QFormLayout(&dialog);
    form->setContentsMargins(20, 20, 20, 20);
    form->setSpacing(12);
    QComboBox *role = new QComboBox;
    role->addItems({"Student", "Lecturer"});
    QLineEdit *name = new QLineEdit;
    form->addRow("Role", role);
    form->addRow("Name", name);
    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    form->addRow(buttons);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    if (dialog.exec() != QDialog::Accepted) return;

    string error;
    int id = library.addMember(role->currentText().toStdString(),
                               name->text().trimmed().toStdString(), error);
    if (id < 0) {
        showError(error);
        return;
    }
    logMessage(QString("Added %1 #%2: %3").arg(role->currentText()).arg(id).arg(name->text()));
    refresh();
}

void MainWindow::onBorrow() {
    int memberId = selectedId(memberTable);
    int itemId = selectedId(itemTable);
    if (memberId < 0 || itemId < 0) {
        QMessageBox::information(this, "Borrow", "Please select one member and one item first.");
        return;
    }
    string error = library.borrowItem(memberId, itemId);
    if (error != "") {
        showError(error);
        return;
    }
    const LibraryItem *item = library.getItem(itemId);
    logMessage(QString("%1 borrowed '%2' (due day %3)")
                   .arg(memberName(memberId))
                   .arg(QString::fromStdString(item->getTitle()))
                   .arg(item->getDueDay()));
    refresh();
}

void MainWindow::onReturn() {
    int itemId = selectedId(itemTable);
    if (itemId < 0) {
        QMessageBox::information(this, "Return", "Please select an item first.");
        return;
    }
    QString title = QString::fromStdString(library.getItem(itemId)->getTitle());
    double fee = 0;
    string error = library.returnItem(itemId, fee);
    if (error != "") {
        showError(error);
        return;
    }
    if (fee > 0) logMessage(QString("Returned '%1' LATE, fine %2").arg(title, money(fee)));
    else logMessage(QString("Returned '%1' on time").arg(title));
    refresh();
}

void MainWindow::onPayFines() {
    int memberId = selectedId(memberTable);
    if (memberId < 0) {
        QMessageBox::information(this, "Pay fines", "Please select a member first.");
        return;
    }
    double paid = 0;
    string error = library.payFines(memberId, paid);
    if (error != "") {
        showError(error);
        return;
    }
    logMessage(QString("%1 paid %2").arg(memberName(memberId), money(paid)));
    refresh();
}

void MainWindow::onAdvance(int days) {
    library.advanceDays(days);
    logMessage(QString("Time advanced by %1 day(s).").arg(days));
    refresh();
}
