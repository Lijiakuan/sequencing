/* $Id: VariantProperties.hpp 371868 2012-08-13 15:10:25Z rafanovi $
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
 */

/// @file VariantProperties.hpp
/// User-defined methods of the data storage class.
///
/// This file was originally generated by application DATATOOL
/// using the following specifications:
/// 'seqfeat.asn'.
///
/// New methods or data members can be added to it if needed.
/// See also: VariantProperties_.hpp


#ifndef OBJECTS_SEQFEAT_VARIANTPROPERTIES_HPP
#define OBJECTS_SEQFEAT_VARIANTPROPERTIES_HPP


// generated includes
#include <objects/seqfeat/VariantProperties_.hpp>

// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

/////////////////////////////////////////////////////////////////////////////
class NCBI_SEQFEAT_EXPORT CVariantProperties : public CVariantProperties_Base
{
    typedef CVariantProperties_Base Tparent;
public:
    // constructor
    CVariantProperties(void);
    // destructor
    ~CVariantProperties(void);

private:
    // Prohibit copy constructor and assignment operator
    CVariantProperties(const CVariantProperties& value);
    CVariantProperties& operator=(const CVariantProperties& value);

    /// Poisoned APIs - abandoned, do not use!!
    /// These APIs reference a data element caught up in a breaking spec
    /// change; use of these APIs will cause problems for many applications
    /// NOTE: ResetProject_data() / IsSetProject_data() / CanGetProject_data()
    /// are deliberately NOT poisoned, since they legitimately repairs data to
    /// a usable state
    const TProject_data& GetProject_data() const;
    TProject_data& SetProject_data();
};

/////////////////// CVariantProperties inline methods

/////////////////// end of CVariantProperties inline methods


END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE


#endif // OBJECTS_SEQFEAT_VARIANTPROPERTIES_HPP
/* Original file checksum: lines: 86, chars: 2568, CRC32: f519da65 */
