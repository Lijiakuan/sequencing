/* $Id: Cit_sub.cpp 371868 2012-08-13 15:10:25Z rafanovi $
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
 *   using specifications from the data definition file
 *   'biblio.asn'.
 */

// standard includes

// generated includes
#include <ncbi_pch.hpp>
#include <objects/biblio/Cit_sub.hpp>
#include <objects/general/Date.hpp>

// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

// destructor
CCit_sub::~CCit_sub(void)
{
}


bool CCit_sub::GetLabelV1(string* label, TLabelFlags flags) const
{
    string date;
    if ( IsSetDate() ) {
        GetDate().GetDate(&date, "%{%M-%D-%}%Y");
    }
    return x_GetLabelV1(label, (flags & fLabel_Unique) != 0, &GetAuthors(),
        IsSetImp() ? &GetImp() : 0,
        0, 0, 0, 0, 0, 0, IsSetDate() ? &date : 0);
}


// Based on FormatCitSub from the C Toolkit's api/asn2gnb5.c.
bool CCit_sub::GetLabelV2(string* label, TLabelFlags flags) const
{
    static const string kToINSD = " to the EMBL/GenBank/DDBJ databases.";

    MaybeAddSpace(label);

    string date;
    if (CanGetDate()) {
        GetDate().GetDate(&date, "%{%2D%|\?\?%}-%{%3N%|\?\?%}-%4Y");
        NStr::ToUpper(date);
    }
    if ( !HasText(date) ) {
        date = "\?\?-\?\?\?-\?\?\?\?";
    }
    *label += "Submitted (" + date + ')';

    if (GetAuthors().CanGetAffil()) {
        string affil;
        GetAuthors().GetAffil().GetLabel(&affil, flags, eLabel_V2);
        if ((flags & fLabel_FlatEMBL) != 0
            &&  !NStr::StartsWith(affil, kToINSD)) {
            *label += kToINSD + '\n';
        } else {
            *label += ' ';
        }
        *label += affil;
    } else if ((flags & fLabel_FlatEMBL) != 0) {
        *label += kToINSD + '\n';
    }

    return true;
}


END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE

/* Original file checksum: lines: 64, chars: 1875, CRC32: ed1dd5e3 */
