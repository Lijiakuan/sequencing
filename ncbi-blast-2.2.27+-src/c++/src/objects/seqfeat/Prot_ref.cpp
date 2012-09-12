/* $Id: Prot_ref.cpp 371868 2012-08-13 15:10:25Z rafanovi $
 * ===========================================================================
 *
 *                            PUBLIC DOMAIN NOTICE
 *               National Center for Biotechnology Information
 *
 *  This software/database is a "United States Government Work" under the
 *  terms of the United States Copyright Act.  It was written as part of
 *  the author's official duties as a United States Government employee and
 *  thus cannot be copyrighted.  This software/database is freely available
 *  to the public for use. The National Library of Medicine and the U.S.
 *  Government have not placed any restriction on its use or reproduction.
 *
 *  Although all reasonable efforts have been taken to ensure the accuracy
 *  and reliability of the software and data, the NLM and the U.S.
 *  Government do not and cannot warrant the performance or results that
 *  may be obtained by using this software or data. The NLM and the U.S.
 *  Government disclaim all warranties, express or implied, including
 *  warranties of performance, merchantability or fitness for any particular
 *  purpose.
 *
 *  Please cite the author in any work or product based on this material.
 *
 * ===========================================================================
 *
 * Author:  .......
 *
 * File Description:
 *   .......
 *
 * Remark:
 *   This code was originally generated by application DATATOOL
 *   using specifications from the ASN data definition file
 *   'seqfeat.asn'.
 */

// standard includes

// generated includes
#include <ncbi_pch.hpp>
#include <objects/seqfeat/Prot_ref.hpp>

// generated classes

#include <corelib/ncbimtx.hpp>
#include <util/line_reader.hpp>
#include <util/util_misc.hpp>
#include <objects/misc/error_codes.hpp>

#define NCBI_USE_ERRCODE_X  Objects_ProtRef

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

// destructor
CProt_ref::~CProt_ref(void)
{
}

// Appends a label to "label" based on content
void CProt_ref::GetLabel(string* label) const
{
    if (IsSetName() && GetName().size() > 0) {
        *label += *GetName().begin();
    } else if (IsSetDesc()) {
        *label += GetDesc();
    } else if (IsSetDb()) {
        GetDb().front()->GetLabel(label);
    }
}


typedef map<string, CProt_ref::EECNumberStatus, PNocase> TECNumberStatusMap;
typedef map<string, string> TECNumberReplacementMap;

static TECNumberStatusMap      s_ECNumberStatusMap;
static TECNumberReplacementMap s_ECNumberReplacementMap;
static bool                    s_ECNumberMapsInitialized = false;
DEFINE_STATIC_FAST_MUTEX(s_ECNumberMutex);

#include "ecnum_ambiguous.inc"
#include "ecnum_deleted.inc"
#include "ecnum_replaced.inc"
#include "ecnum_specific.inc"

static void s_ProcessECNumberLine(const CTempString& line,
                                  CProt_ref::EECNumberStatus status)
{
    if (status == CProt_ref::eEC_replaced) {
        SIZE_TYPE tab_pos = line.find('\t');
        if (tab_pos == NPOS) {
            ERR_POST_X(1, Warning << "No tab in ecnum_replaced entry " << line
                       << "; disregarding");
        } else {
            string lhs(line.substr(0, tab_pos)), rhs(line.substr(tab_pos + 1));
            s_ECNumberStatusMap[lhs]      = status;
            s_ECNumberReplacementMap[lhs] = rhs;
        }
    } else {
        SIZE_TYPE tab_pos = line.find('\t');
        if (tab_pos == NPOS) {
            s_ECNumberStatusMap[line] = status;
        } else {
            string lhs(line.substr(0, tab_pos));
            s_ECNumberStatusMap[lhs] = status;
        }
    }
}


static void s_LoadECNumberTable(const string& dir, const string& name,
                                const char* const *fallback,
                                size_t fallback_count,
                                CProt_ref::EECNumberStatus status)
{
    CRef<ILineReader> lr;
    if ( !dir.empty() ) {
        lr.Reset(ILineReader::New
                 (CDirEntry::MakePath(dir, "ecnum_" + name, "txt")));
    }
    if (lr.Empty()) {
        while (fallback_count--) {
            s_ProcessECNumberLine(*fallback++, status);
        }
    } else {
        do {
            s_ProcessECNumberLine(*++*lr, status);
        } while ( !lr->AtEOF() );
    }
}


static void s_InitializeECNumberMaps(void)
{
    CFastMutexGuard GUARD(s_ECNumberMutex);
    if (s_ECNumberMapsInitialized) {
        return;
    }
    string dir;
    {{
        string file = g_FindDataFile("ecnum_specific.txt");
        if ( !file.empty() ) {
            dir = CDirEntry::AddTrailingPathSeparator(CDirEntry(file).GetDir());
        }
    }}
    if (dir.empty()) {
        ERR_POST_X(2, Info << "s_InitializeECNumberMaps: "
                   "falling back on built-in data.");
    }
#define LOAD_EC(x) s_LoadECNumberTable \
    (dir, #x, kECNum_##x, sizeof(kECNum_##x) / sizeof(*kECNum_##x), \
     CProt_ref::eEC_##x)
    LOAD_EC(specific);
    LOAD_EC(ambiguous);
    LOAD_EC(replaced);
    LOAD_EC(deleted);
#undef LOAD_EC
    s_ECNumberMapsInitialized = true;
}


CProt_ref::EECNumberStatus CProt_ref::GetECNumberStatus(const string& ecno)
{
    if ( !s_ECNumberMapsInitialized ) {
        s_InitializeECNumberMaps();
    }
    TECNumberStatusMap::const_iterator it = s_ECNumberStatusMap.find(ecno);
    if (it == s_ECNumberStatusMap.end()) {
        return eEC_unknown;
    } else {
        return it->second;
    }
}


const string& CProt_ref::GetECNumberReplacement(const string& old_ecno)
{
    if ( !s_ECNumberMapsInitialized ) {
        s_InitializeECNumberMaps();
    }
    TECNumberReplacementMap::const_iterator it
        = s_ECNumberReplacementMap.find(old_ecno);
    if (it == s_ECNumberReplacementMap.end()) {
        NCBI_THROW(CCoreException, eInvalidArg,
                   "No replacement defined for EC number " + old_ecno);
        // alternatively, could return old_ecno or kEmptyStr
    } else {
        return it->second;
    }
}


bool CProt_ref::IsValidECNumberFormat (const string&  ecno)
{
    char     ch;
    bool     is_ambig;
    int      numdashes;
    int      numdigits;
    int      numperiods;

    if (NStr::IsBlank (ecno)) {
        return false;
    }

    is_ambig = false;
    numperiods = 0;
    numdigits = 0;
    numdashes = 0;

    string::const_iterator sit = ecno.begin();
    while (sit != ecno.end()) {
        ch = *sit;
        if (isdigit (ch)) {
            numdigits++;
            if (is_ambig) return false;
        } else if (ch == '-') {
            numdashes++;
            is_ambig = true;
        } else if (ch == 'n') {
            if (numperiods == 3 && numdigits == 0) {
                string::const_iterator sit2 = sit;
                sit2++;
                if (isdigit (*sit2)) {
                    // allow/ignore n in first position of fourth number to not mean ambiguous, if followed by digit
                } else {
                    numdashes++;
                    is_ambig = true;
                }
            } else {
                numdashes++;
                is_ambig = true;
            }
        } else if (ch == '.') {
            numperiods++;
            if (numdigits > 0 && numdashes > 0) return false;
            if (numdigits == 0 && numdashes == 0) return false;
            if (numdashes > 1) return false;
            numdigits = 0;
            numdashes = 0;
        }
        ++sit;
    }

    if (numperiods == 3) {
        if (numdigits > 0 && numdashes > 0) return false;
        if (numdigits > 0 || numdashes == 1) return true;
    }

    return false;
}


END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE

/* Original file checksum: lines: 61, chars: 1885, CRC32: 4ba9347a */
