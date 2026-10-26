#pragma once

#include "../BasePage.h"
#include "HandoverTypes.h"
#include <vector>

class CDailyReportPage : public CBasePage
{
public:
    BOOL CreatePage(CWnd* p, const CRect& r, UINT id);

    // 인쇄/미리보기/PDF가 모두 같은 레이아웃을 사용합니다.
    void DrawReport(CDC& dc, const CRect& pageRect) const;

private:
    enum
    {
        IDC_REPORT_SEARCH = 3601,
        IDC_REPORT_PREVIEW = 3602,
        IDC_REPORT_PDF = 3603,
        IDC_REPORT_EXCEL = 3604,
        IDC_REPORT_PRINT = 3605
    };

    struct DefectRecord
    {
        CString inspectionId;
        CString inspectedAt;
        CString tireId;
        CString defectType;
        CString detail;
        CString imagePath;
    };

    struct ReportViewData
    {
        bool sample = false;
        CString date;
        CString author;
        CString shift;
        CString generatedAt;

        long long total = 0;
        long long pass = 0;
        long long fail = 0;
        double failRate = 0.0;
        bool fromDatabase = false;
        long long wheelDamage = 0;
        long long tireDamage = 0;
        long long bothDamage = 0;
        long long unclassified = 0;
        std::vector<DefectRecord> defectRecords;

        std::vector<int> hourlyTotal;
        std::vector<int> hourlyPass;
        std::vector<int> hourlyFail;
        std::vector<CString> hourlyLabel;

        std::vector<HandoverItem> handovers;
    };

    CEdit* m_dateEdit = nullptr;
    CEdit* m_previewEdit = nullptr;
    CModernCard m_totalCard;
    CModernCard m_passCard;
    CModernCard m_failCard;
    CModernCard m_rateCard;

    std::vector<HandoverItem> m_filteredHandovers;
    long long m_total = 0;
    long long m_pass = 0;
    long long m_fail = 0;
    bool m_hasServerReport = false;
    ReportViewData m_serverReport;
    bool LoadServerReport(const CString& date, ReportViewData& report) const;

    CString GetReportDate() const;
    void RefreshReport();
    void UpdateSummaryCards();
    CString BuildReportText() const;
    ReportViewData BuildReportViewData() const;

    // 실제 OOXML 패키지(.xlsx)로 저장하여 한셀/Excel 호환성을 확보합니다.
    bool ExportExcelXlsx(const CString& path) const;
    bool PrintReportToDC(HDC hdc, const CString& documentName, const CString* outputPath = nullptr) const;

    static bool ExtractCount(const CString& message, LPCTSTR label, long long& value);

    afx_msg void OnSearch();
    afx_msg void OnPreview();
    afx_msg void OnPdf();
    afx_msg void OnExcel();
    afx_msg void OnPrint();
 
    DECLARE_MESSAGE_MAP()
};
