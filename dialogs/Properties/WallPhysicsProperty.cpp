#include "stdafx.h"
#include "Properties/WallPhysicsProperty.h"
#include <WindowsX.h>

WallPhysicsProperty::WallPhysicsProperty(VectorProtected<ISelect> *pvsel) : BasePropertyDialog(IDD_PROPWALL_PHYSICS, pvsel)
{
}

void WallPhysicsProperty::UpdateVisuals()
{
    for (int i = 0; i < m_pvsel->Size(); i++)
    {
        Surface *wall = (Surface*)m_pvsel->ElementAt(i);
        PropertyDialog::UpdateMaterialComboBox(wall->GetPTable()->GetMaterialList(), m_physicsMaterialCombo, wall->m_d.m_szPhysicsMaterial);

        PropertyDialog::SetFloatTextbox(m_hitThresholdEdit, wall->m_d.m_threshold);
        PropertyDialog::SetFloatTextbox(m_slingshotForceEdit, wall->m_d.m_slingshotforce);
        PropertyDialog::SetFloatTextbox(m_slingshotThresholdEdit, wall->m_d.m_slingshot_threshold);
        PropertyDialog::SetFloatTextbox(m_elasticityEdit, wall->m_d.m_elasticity);
        PropertyDialog::SetFloatTextbox(m_frictionEdit, wall->m_d.m_friction);
        PropertyDialog::SetFloatTextbox(m_scatterAngleEdit, wall->m_d.m_scatter);
        PropertyDialog::SetCheckboxState(::GetDlgItem(GetHwnd(), IDC_HAS_HITEVENT_CHECK), wall->m_d.m_hitEvent);
        PropertyDialog::SetCheckboxState(::GetDlgItem(GetHwnd(), IDC_OVERWRITE_MATERIAL_SETTINGS), wall->m_d.m_overwritePhysics);
        PropertyDialog::SetCheckboxState(::GetDlgItem(GetHwnd(), 11), wall->m_d.m_droppable);
        PropertyDialog::SetCheckboxState(::GetDlgItem(GetHwnd(), IDC_COLLIDABLE_CHECK), wall->m_d.m_collidable);
        PropertyDialog::SetCheckboxState(::GetDlgItem(GetHwnd(), 116), wall->m_d.m_isBottomSolid);

        if (!wall->m_d.m_collidable)
        {
            ::EnableWindow(::GetDlgItem(GetHwnd(), 116), FALSE);
            ::EnableWindow(::GetDlgItem(GetHwnd(), IDC_HAS_HITEVENT_CHECK), FALSE);
            ::EnableWindow(::GetDlgItem(GetHwnd(), IDC_OVERWRITE_MATERIAL_SETTINGS), FALSE);
            m_hitThresholdEdit.EnableWindow(FALSE);
            m_physicsMaterialCombo.EnableWindow(FALSE);
            m_elasticityEdit.EnableWindow(FALSE);
            m_frictionEdit.EnableWindow(FALSE);
            m_scatterAngleEdit.EnableWindow(FALSE);
            m_slingshotForceEdit.EnableWindow(FALSE);
            m_slingshotThresholdEdit.EnableWindow(FALSE);
        }
        else
        {
            ::EnableWindow(::GetDlgItem(GetHwnd(), 116), TRUE);
            ::EnableWindow(::GetDlgItem(GetHwnd(), IDC_HAS_HITEVENT_CHECK), TRUE);
            ::EnableWindow(::GetDlgItem(GetHwnd(), IDC_OVERWRITE_MATERIAL_SETTINGS), TRUE);
            m_slingshotForceEdit.EnableWindow(TRUE);
            m_slingshotThresholdEdit.EnableWindow(TRUE);
            if (wall->m_d.m_hitEvent)
                m_hitThresholdEdit.EnableWindow(TRUE);
            else
                m_hitThresholdEdit.EnableWindow(FALSE);

            if (!wall->m_d.m_overwritePhysics)
            {
                m_physicsMaterialCombo.EnableWindow(TRUE);
                m_elasticityEdit.EnableWindow(FALSE);
                m_frictionEdit.EnableWindow(FALSE);
                m_scatterAngleEdit.EnableWindow(FALSE);
            }
            else
            {
                m_physicsMaterialCombo.EnableWindow(FALSE);
                m_elasticityEdit.EnableWindow(TRUE);
                m_frictionEdit.EnableWindow(TRUE);
                m_scatterAngleEdit.EnableWindow(TRUE);
            }
        }
    }
}

void WallPhysicsProperty::UpdateProperties(const int dispid)
{
    for (int i = 0; i < m_pvsel->Size(); i++)
    {
        Surface *wall = (Surface*)m_pvsel->ElementAt(i);
        switch (dispid)
        {
            case IDC_HIT_THRESHOLD_EDIT:
                PropertyDialog::StartUndo(wall);
                wall->m_d.m_threshold = PropertyDialog::GetFloatTextbox(m_hitThresholdEdit);
                PropertyDialog::EndUndo(wall);
                break;
            case IDC_HAS_HITEVENT_CHECK:
                PropertyDialog::StartUndo(wall);
                wall->m_d.m_hitEvent = PropertyDialog::GetCheckboxState(::GetDlgItem(GetHwnd(), dispid));
                PropertyDialog::EndUndo(wall);
                break;
            case 11:
                PropertyDialog::StartUndo(wall);
                wall->m_d.m_droppable = PropertyDialog::GetCheckboxState(::GetDlgItem(GetHwnd(), dispid));
                PropertyDialog::EndUndo(wall);
                break;
            case 14:
                PropertyDialog::StartUndo(wall);
                wall->m_d.m_slingshotforce = PropertyDialog::GetFloatTextbox(m_slingshotForceEdit);
                PropertyDialog::EndUndo(wall);
                break;
            case IDC_ELASTICITY_EDIT:
                PropertyDialog::StartUndo(wall);
                wall->m_d.m_elasticity = PropertyDialog::GetFloatTextbox(m_elasticityEdit);
                PropertyDialog::EndUndo(wall);
                break;
            case IDC_COLLIDABLE_CHECK:
                PropertyDialog::StartUndo(wall);
                wall->m_d.m_collidable = PropertyDialog::GetCheckboxState(::GetDlgItem(GetHwnd(), dispid));
                PropertyDialog::EndUndo(wall);
                break;
            case 427:
                PropertyDialog::StartUndo(wall);
                wall->m_d.m_slingshot_threshold = PropertyDialog::GetFloatTextbox(m_slingshotThresholdEdit);
                PropertyDialog::EndUndo(wall);
                break;
            case IDC_FRICTION_EDIT:
                PropertyDialog::StartUndo(wall);
                wall->m_d.m_friction = PropertyDialog::GetFloatTextbox(m_frictionEdit);
                PropertyDialog::EndUndo(wall);
                break;
            case IDC_SCATTER_ANGLE_EDIT:
                PropertyDialog::StartUndo(wall);
                wall->m_d.m_scatter = PropertyDialog::GetFloatTextbox(m_scatterAngleEdit);
                PropertyDialog::EndUndo(wall);
                break;
            case 116:
                PropertyDialog::StartUndo(wall);
                wall->m_d.m_isBottomSolid = PropertyDialog::GetCheckboxState(::GetDlgItem(GetHwnd(), dispid));
                PropertyDialog::EndUndo(wall);
                break;
            case IDC_OVERWRITE_MATERIAL_SETTINGS:
                PropertyDialog::StartUndo(wall);
                wall->m_d.m_overwritePhysics = PropertyDialog::GetCheckboxState(::GetDlgItem(GetHwnd(), dispid));
                PropertyDialog::EndUndo(wall);
                break;
            case IDC_MATERIAL_COMBO:
                PropertyDialog::StartUndo(wall);
                PropertyDialog::GetComboBoxText(m_physicsMaterialCombo, wall->m_d.m_szPhysicsMaterial);
                PropertyDialog::EndUndo(wall);
                break;
            default:
                break;
        }
    }
    UpdateVisuals();
}

BOOL WallPhysicsProperty::OnInitDialog()
{
    AttachItem(IDC_HIT_THRESHOLD_EDIT, m_hitThresholdEdit);
    AttachItem(14, m_slingshotForceEdit);
    AttachItem(427, m_slingshotThresholdEdit);
    AttachItem(IDC_MATERIAL_COMBO4, m_physicsMaterialCombo);
    AttachItem(IDC_ELASTICITY_EDIT, m_elasticityEdit);
    AttachItem(IDC_FRICTION_EDIT, m_frictionEdit);
    AttachItem(IDC_SCATTER_ANGLE_EDIT, m_scatterAngleEdit);
    UpdateVisuals();
    return TRUE;
}

BOOL WallPhysicsProperty::OnCommand(WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    const int dispID = LOWORD(wParam);

    switch (HIWORD(wParam))
    {
        case EN_KILLFOCUS:
        case CBN_KILLFOCUS:
        case BN_CLICKED:
        {
            UpdateProperties(dispID);
            return TRUE;
        }
    }
    return FALSE;
}
