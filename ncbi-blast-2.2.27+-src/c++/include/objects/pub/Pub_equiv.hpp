/* $Id: Pub_equiv.hpp 371868 2012-08-13 15:10:25Z rafanovi $
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
 *   'pub.asn'.
 */

#ifndef OBJECTS_PUB_PUB_EQUIV_HPP
#define OBJECTS_PUB_PUB_EQUIV_HPP


// generated includes
#include <objects/pub/Pub_equiv_.hpp>

#include <objects/biblio/citation_base.hpp>

// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

class NCBI_PUB_EXPORT CPub_equiv
    : public CPub_equiv_Base, public IAbstractCitation
{
    typedef CPub_equiv_Base Tparent;
public:
    // constructor
    CPub_equiv(void);
    // destructor
    ~CPub_equiv(void);
    
    /// Append a label to "label" based on content
    bool GetLabel(string* label, TLabelFlags flags = 0,
                  ELabelVersion version = eLabel_DefaultVersion) const;

private:
    // Prohibit copy constructor and assignment operator
    CPub_equiv(const CPub_equiv& value);
    CPub_equiv& operator=(const CPub_equiv& value);

};

/////////////////// CPub_equiv inline methods

// constructor
inline
CPub_equiv::CPub_equiv(void)
{
}


/////////////////// end of CPub_equiv inline methods


END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE


#endif // OBJECTS_PUB_PUB_EQUIV_HPP
/* Original file checksum: lines: 90, chars: 2385, CRC32: fee61eab */
