/* $Id: Object_id.hpp 371868 2012-08-13 15:10:25Z rafanovi $
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
 *   'general.asn'.
 */

#ifndef OBJECTS_GENERAL_OBJECT_ID_HPP
#define OBJECTS_GENERAL_OBJECT_ID_HPP


// generated includes
#include <objects/general/Object_id_.hpp>

// generated classes

#include <serial/objhook.hpp>
#include <map>

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

class NCBI_GENERAL_EXPORT CObject_id : public CObject_id_Base
{
    typedef CObject_id_Base Tparent;
public:
    // constructor
    CObject_id(void);
    // destructor
    ~CObject_id(void);

    // identical ids?
    bool Match(const CObject_id& oid2) const;
    int Compare(const CObject_id& oid2) const;
    bool operator<(const CObject_id& id2) const;

    // format contents into a stream
    ostream& AsString(ostream &s) const;
private:
    // Prohibit copy constructor & assignment operator
    CObject_id(const CObject_id&);
    CObject_id& operator= (const CObject_id&);
};



/////////////////// CObject_id inline methods

// constructor
inline
CObject_id::CObject_id(void)
{
}



inline
bool CObject_id::operator<(const CObject_id& id2) const
{
    return Compare(id2) < 0;
}


/////////////////// end of CObject_id inline methods

/////////////////////////////////////////////////////////////////////////////
// CReadSharedObjectIdHookBase
//   base class for read hooks for shared Object-id objects.
/////////////////////////////////////////////////////////////////////////////

class NCBI_GENERAL_EXPORT CReadSharedObjectIdHookBase
    : public CReadClassMemberHook
{
public:
    /// Returns shared version of Object-id with specified 'str' field value.
    /// Can be stored for later read-only use.
    CObject_id& GetSharedObject_id(const string& id);
    /// Returns shared version of Object-id with specified 'id' field value.
    /// Can be stored for later read-only use.
    CObject_id& GetSharedObject_id(int id);

    /// Returns shared version of argument Object-id.
    /// Can be stored for later read-only use.
    CObject_id& GetSharedObject_id(const CObject_id& oid) {
        return oid.IsStr()?
            GetSharedObject_id(oid.GetStr()):
            GetSharedObject_id(oid.GetId());
    }

    /// Reads Object-id and returns reference to its shared version.
    /// Can be stored for later read-only use.
    CObject_id& ReadSharedObject_id(CObjectIStream& in);
    
protected:
    CObject_id m_Temp;

private:
    typedef map<string, CRef<CObject_id> > TMapByStr;
    typedef map<int, CRef<CObject_id> > TMapByInt;
    TMapByStr m_MapByStr;
    TMapByInt m_MapByInt;
};


/////////////////////////////////////////////////////////////////////////////


END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE


#endif // OBJECTS_GENERAL_OBJECT_ID_HPP
