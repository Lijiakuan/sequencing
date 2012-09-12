/* $Id: Sparse_align.hpp 371868 2012-08-13 15:10:25Z rafanovi $
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
 * Author:  Kamen Todorov
 *
 * File Description:
 *   Sparse-align
 *
 */

/// @file Sparse_align.hpp
/// User-defined methods of the data storage class.
///
/// This file was originally generated by application DATATOOL
/// using the following specifications:
/// 'seqalign.asn'.
///
/// New methods or data members can be added to it if needed.
/// See also: Sparse_align_.hpp


#ifndef OBJECTS_SEQALIGN_SPARSE_ALIGN_HPP
#define OBJECTS_SEQALIGN_SPARSE_ALIGN_HPP


// generated includes
#include <objects/seqalign/Sparse_align_.hpp>

// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

/////////////////////////////////////////////////////////////////////////////
class NCBI_SEQALIGN_EXPORT CSparse_align : public CSparse_align_Base
{
    typedef CSparse_align_Base Tparent;
public:
    // constructor
    CSparse_align(void);
    // destructor
    ~CSparse_align(void);

    /// types
    typedef int TDim;

    /// Validators
    void Validate    (bool full_test = false) const;
    TDim CheckNumRows(void)                   const {
        return 2;
    }
    TNumseg CheckNumSegs(void)                const;

private:
    // Prohibit copy constructor and assignment operator
    CSparse_align(const CSparse_align& value);
    CSparse_align& operator=(const CSparse_align& value);

};

/////////////////// CSparse_align inline methods

// constructor
inline
CSparse_align::CSparse_align(void)
{
}


/////////////////// end of CSparse_align inline methods


END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE


#endif // OBJECTS_SEQALIGN_SPARSE_ALIGN_HPP
/* Original file checksum: lines: 86, chars: 2479, CRC32: f75e75f3 */