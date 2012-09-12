/* $Id: Seq_data.cpp 371868 2012-08-13 15:10:25Z rafanovi $
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
 *   'seq.asn'.
 */

// standard includes

// generated includes
#include <ncbi_pch.hpp>
#include <objects/seq/Seq_data.hpp>

// additional includes
#include <objects/seq/IUPACaa_.hpp>
#include <objects/seq/IUPACna.hpp>
#include <objects/seq/NCBI2na_.hpp>
#include <objects/seq/NCBI4na_.hpp>
#include <objects/seq/NCBI8aa_.hpp>
#include <objects/seq/NCBI8na_.hpp>
#include <objects/seq/NCBIeaa_.hpp>
#include <objects/seq/NCBIpaa_.hpp>
#include <objects/seq/NCBIpna_.hpp>
#include <objects/seq/NCBIstdaa_.hpp>
#include <corelib/ncbiexpt.hpp>

// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

// constructor
CSeq_data::CSeq_data(const string& value, E_Choice index)
{


    // Does value have to be validated
    // create seq type data holder
    switch (index) {
    case e_Iupacna:
    case e_Iupacaa:
    case e_Ncbieaa:
        DoConstruct (value, index);
        break;

    case e_Ncbi2na:
    case e_Ncbi4na:
    case e_Ncbi8na:
    case e_Ncbipna:
    case e_Ncbi8aa:
    case e_Ncbipaa:
    case e_Ncbistdaa:
    {
        vector< char > v;
        v.resize (value.size());
        memcpy(&v[0], value.c_str(), value.size());
        DoConstruct (v, index);
        break;
    }
    default:
        // throw error
        NCBI_THROW (CException, eUnknown,
            "CSeq_data constructor: Invalid E_Choice index");
    }
}

CSeq_data::CSeq_data(const vector< char >& value, E_Choice index)
{
    // Does value have to be validated
    // create seq type data holder
    switch (index) {
    case e_Iupacna:
    case e_Iupacaa:
    case e_Ncbieaa:
    {
        string s;
        s.assign (&value[0], value.size());
        DoConstruct (s, index);
        break;
    }
    case e_Ncbi2na:
    case e_Ncbi4na:
    case e_Ncbi8na:
    case e_Ncbipna:
    case e_Ncbi8aa:
    case e_Ncbipaa:
    case e_Ncbistdaa:
        DoConstruct (value, index);
        break;

    default:
        // throw error
        NCBI_THROW (CException, eUnknown,
            "CSeq_data constructor: Invalid E_Choice index");
    }
}

// destructor
CSeq_data::~CSeq_data(void)
{
}

void CSeq_data::DoConstruct(const string& value, E_Choice index)
{

    switch (index) {
    case e_Iupacna:
        SetIupacna() = CIUPACna(value);
        break;
    case e_Iupacaa:
        SetIupacaa() = CIUPACaa(value);
        break;
    case e_Ncbieaa:
        SetNcbieaa() = CNCBIeaa(value);
        break;
    default:
        // throw an error
        NCBI_THROW (CException, eUnknown,
            "CSeq_data::DoConstruct: Invalid E_Choice index");
    }
}

void CSeq_data::DoConstruct(const vector< char >& value, E_Choice index)
{
    switch (index) {
    case e_Ncbi2na:
        SetNcbi2na().Set() = value;
        break;
    case e_Ncbi4na:
        SetNcbi4na().Set() = value;
        break;
    case e_Ncbi8na:
        SetNcbi8na().Set() = value;
        break;
    case e_Ncbipna:
        SetNcbipna().Set() = value;
        break;
    case e_Ncbi8aa:
        SetNcbi8aa().Set() = value;
        break;
    case e_Ncbipaa:
        SetNcbipaa().Set() = value;
        break;
    case e_Ncbistdaa:
        SetNcbistdaa().Set() = value;
        break;
    default:
        // throw an error
        NCBI_THROW (CException, eUnknown,
            "CSeq_data::DoConstruct: Invalid E_Choice index");
    }
}

END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE

/* Original file checksum: lines: 64, chars: 1872, CRC32: 4f4e2fd */