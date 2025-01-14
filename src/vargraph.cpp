/*         vargraph.cpp   */
/*  This file is part of COLLATINUS.
 *
 *  COLLATINUS is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  COLLATINVS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with COLLATINUS; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * © Yves Ouvrard, 2009 - 2019
 */

#include "vargraph.h"

DialogVG::DialogVG(QStringList l, MainWindow* parent)
{
    mainwin = parent;
    resize(mainwin->width()/2, mainwin->height()/2);
    tabVarGraph = new QWidget();
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(6);
    verticalLayout->setContentsMargins(11, 11, 11, 11);
    splitterVarGraph = new QSplitter(tabVarGraph);
    splitterVarGraph->setOrientation(Qt::Horizontal);
    layoutWidget = new QWidget(splitterVarGraph);
    verticalLayoutConf = new QVBoxLayout(layoutWidget);
    verticalLayoutConf->setSpacing(6);
    verticalLayoutConf->setContentsMargins(11, 11, 11, 11);
    verticalLayoutConf->setContentsMargins(0, 0, 0, 0);
    label_3 = new QLabel(layoutWidget);
    verticalLayoutConf->addWidget(label_3);
    horizontalLayoutBtnPre = new QHBoxLayout();
    horizontalLayoutBtnPre->setSpacing(6);
    horizontalSpacerPre = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayoutBtnPre->addItem(horizontalSpacerPre);
    verticalLayoutConf->addLayout(horizontalLayoutBtnPre);
    formLayoutCochesVar = new QFormLayout();
    formLayoutCochesVar->setSpacing(6);
    formLayoutCochesVar->setContentsMargins(13, 13, -1, -1);
    labelVariante = new QLabel(layoutWidget);
    formLayoutCochesVar->setWidget(0, QFormLayout::LabelRole, labelVariante);
    checkBoxAe = new QCheckBox(layoutWidget);
    formLayoutCochesVar->setWidget(1, QFormLayout::LabelRole, checkBoxAe);
    checkBox_H = new QCheckBox(layoutWidget);
    formLayoutCochesVar->setWidget(2, QFormLayout::LabelRole, checkBox_H);
    checkBox_Mihi = new QCheckBox(layoutWidget);
    formLayoutCochesVar->setWidget(3, QFormLayout::LabelRole, checkBox_Mihi);
    checkBox_IJ = new QCheckBox(layoutWidget);
    formLayoutCochesVar->setWidget(4, QFormLayout::LabelRole, checkBox_IJ);
    checkBox_UV = new QCheckBox(layoutWidget);
    formLayoutCochesVar->setWidget(5, QFormLayout::LabelRole, checkBox_UV);
    checkBox_TICI = new QCheckBox(layoutWidget);
    formLayoutCochesVar->setWidget(6, QFormLayout::LabelRole, checkBox_TICI);
    checkBox_MPN = new QCheckBox(layoutWidget);
    formLayoutCochesVar->setWidget(7, QFormLayout::LabelRole, checkBox_MPN);
    checkBox_PH = new QCheckBox(layoutWidget);
    formLayoutCochesVar->setWidget(8, QFormLayout::LabelRole, checkBox_PH);
    verticalLayoutConf->addLayout(formLayoutCochesVar);
    splitterVarGraph->addWidget(layoutWidget);
    splitter_2 = new QSplitter(splitterVarGraph);
    splitter_2->setOrientation(Qt::Vertical);
    plainTextEditVariantes = new QPlainTextEdit(splitter_2);
    splitter_2->addWidget(plainTextEditVariantes);
    layoutWidget1 = new QWidget(splitter_2);
    verticalLayout_4 = new QVBoxLayout(layoutWidget1);
    verticalLayout_4->setSpacing(6);
    verticalLayout_4->setContentsMargins(11, 11, 11, 11);
    verticalLayout_4->setContentsMargins(0, 0, 0, 0);
    splitter_2->addWidget(layoutWidget1);
    splitterVarGraph->addWidget(splitter_2);
    verticalLayout->addWidget(splitterVarGraph);

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Apply);
    verticalLayout->addWidget(buttonBox);

    buttonBox->button(QDialogButtonBox::Close)->setText(tr("Fermer"));
    buttonBox->button(QDialogButtonBox::Apply)->setText(tr("Appliquer"));

    // étiquettes
    etiquettes();
    initCoches(l);
    connecte();
}

void DialogVG::etiquettes()
{
    label_3->setText("Ces changements ne sont valables<br/>\n"
                     "que pour la session courante. On peut éditer<br/>\n"
                     "le module en installant l'application Ecce.<br/>\n"
                     "Cf. la documentation");
    labelVariante->setText(QApplication::translate("MainWindow", "variante", Q_NULLPTR));
    checkBoxAe->setText(QApplication::translate("MainWindow", "ae > e", Q_NULLPTR));
    checkBox_H->setText(QApplication::translate("MainWindow", "h > -", Q_NULLPTR));
    checkBox_Mihi->setText(QApplication::translate("MainWindow", "mihi > michi", Q_NULLPTR));
    checkBox_IJ->setText(QApplication::translate("MainWindow", "I > J", Q_NULLPTR));
    checkBox_UV->setText(QApplication::translate("MainWindow", "U > V", Q_NULLPTR));
    checkBox_TICI->setText(QApplication::translate("MainWindow", "ti > ci", Q_NULLPTR));
    checkBox_MPN->setText(QApplication::translate("MainWindow", "mn > mpn", Q_NULLPTR));
    checkBox_PH->setText(QApplication::translate("MainWindow", "ph > f", Q_NULLPTR));
}

QStringList DialogVG::lignes()
{
    return tv;
}

void DialogVG::coche()
{
    tv = plainTextEditVariantes->toPlainText().split("\n");
    //plainTextEditVariantes->clear();
    if (checkBoxAe->isChecked())
        tv.append(lvg.at(0));
    else tv.removeAll(lvg.at(0));
    if (checkBox_H->isChecked())
        tv.append(lvg.at(1));
    else tv.removeAll(lvg.at(1));
    if (checkBox_Mihi->isChecked())
        tv.append(lvg.at(2));
    else tv.removeAll(lvg.at(2));
    if (checkBox_IJ->isChecked())
        tv.append(lvg.at(3));
    else tv.removeAll(lvg.at(3));
    if (checkBox_UV->isChecked())
        tv.append(lvg.at(4));
    else tv.removeAll(lvg.at(4));
    if (checkBox_TICI->isChecked())
        tv.append(lvg.at(5));
    else tv.removeAll(lvg.at(5));
    if (checkBox_MPN->isChecked())
        tv.append(lvg.at(6));
    else tv.removeAll(lvg.at(6));
    if (checkBox_PH->isChecked())
        tv.append(lvg.at(7));
    else tv.removeAll(lvg.at(7));
    tv.removeDuplicates();
    plainTextEditVariantes->setPlainText(tv.join("\n"));
}


void DialogVG::connecte()
{
    connect(checkBoxAe, SIGNAL(stateChanged(int)), this, SLOT(coche()));
    connect(checkBox_H, SIGNAL(stateChanged(int)), this, SLOT(coche()));
    connect(checkBox_Mihi, SIGNAL(stateChanged(int)), this, SLOT(coche()));
    connect(checkBox_IJ, SIGNAL(stateChanged(int)), this, SLOT(coche()));
    connect(checkBox_UV, SIGNAL(stateChanged(int)), this, SLOT(coche()));
    connect(checkBox_TICI, SIGNAL(stateChanged(int)), this, SLOT(coche()));
    connect(checkBox_MPN, SIGNAL(stateChanged(int)), this, SLOT(coche()));
    connect(checkBox_PH, SIGNAL(stateChanged(int)), this, SLOT(coche()));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(close()));
}

void DialogVG::initCoches(QStringList ll)
{
    plainTextEditVariantes->setPlainText(ll.join('\n'));
    checkBoxAe->setChecked(ll.contains(lvg.at(0)));
    checkBox_H->setChecked(ll.contains(lvg.at(1)));
    checkBox_Mihi->setChecked(ll.contains(lvg.at(2)));
    checkBox_IJ->setChecked(ll.contains(lvg.at(3)));
    checkBox_UV->setChecked(ll.contains(lvg.at(4)));
    checkBox_TICI->setChecked(ll.contains(lvg.at(5)));
    checkBox_MPN->setChecked(ll.contains(lvg.at(6)));
    checkBox_PH->setChecked(ll.contains(lvg.at(7)));
}
