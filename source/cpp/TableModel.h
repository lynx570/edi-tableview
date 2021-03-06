#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
class Property;

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

    Q_PROPERTY(QStringList columnNames  READ columnNames WRITE setColumnNames   NOTIFY columnNamesChanged)
    Q_PROPERTY(QStringList rowNames     READ rowNames    WRITE setRowNames      NOTIFY rowNamesChanged)
    Q_PROPERTY(int count                READ count       NOTIFY countChanged)

    Q_ENUMS(Roles)
public:
    explicit                TableModel(QObject *parent=nullptr);
                            ~TableModel() override = default;
    int                     rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int                     columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant                data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant                headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    enum                    Roles {CellDataRole = Qt::UserRole+1, CellTypeRole,CellFlagsRole, CellEditorRole, CellOptionRole};
    QHash<int, QByteArray>  roleNames() const override;
    // EDITING
    bool                    setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags           flags(const QModelIndex &index) const override;
    // PROPERTIES
    QStringList             columnNames() const;
    QStringList             rowNames() const;
    int                     count() const;
public slots:
    void                    testData();
    void                    clear();
signals:
    void                    columnNamesChanged(QStringList columnNames);
    void                    rowNamesChanged(QStringList rowNames);
    void                    countChanged(int count);
private:
    bool                    indexInRange(const QModelIndex &index) const;
    void                    setColumnNames(QStringList columnNames);
    void                    setRowNames(QStringList rowNames);

    QList<Property*>        properties_;
    QStringList             columnNames_;
    QStringList             rowNames_;

    void clearData();
    void createIncrementalRowLabel();
};

#endif // TABLEMODEL_H
