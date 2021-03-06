//
//  Copyright (c) 1996-2006 by Autodesk, Inc.
//
//  By using this code, you are agreeing to the terms and conditions of
//  the License Agreement included in the documentation for this code.
//
//  AUTODESK MAKES NO WARRANTIES, EXPRESS OR IMPLIED, AS TO THE CORRECTNESS
//  OF THIS CODE OR ANY DERIVATIVE WORKS WHICH INCORPORATE IT. AUTODESK
//  PROVIDES THE CODE ON AN "AS-IS" BASIS AND EXPLICITLY DISCLAIMS ANY
//  LIABILITY, INCLUDING CONSEQUENTIAL AND INCIDENTAL DAMAGES FOR ERRORS,
//  OMISSIONS, AND OTHER PROBLEMS IN THE CODE.
//
//  Use, duplication, or disclosure by the U.S. Government is subject to
//  restrictions set forth in FAR 52.227-19 (Commercial Computer Software
//  Restricted Rights) and DFAR 252.227-7013(c)(1)(ii) (Rights in Technical
//  Data and Computer Software), as applicable.
//

#if !defined POLYTRI_HEADER
#define POLYTRI_HEADER

///
///\file        dwf/whiptk/polytri.h
///

#include "whiptk/whipcore.h"
#include "whiptk/file.h"
#include "whiptk/drawable.h"
#include "whiptk/pointset.h"

/** \addtogroup groupDrawable
 *  @{
 */

/// A drawable describing a polytriangle (a collection of contiguous triangles).
/** \image html Polytriangle.png "Polytriangle point ordering details"
 *
 */
class WHIPTK_API WT_Polytriangle : public WT_Drawable, public WT_Point_Set
{
	friend class WT_W2D_Class_Factory;
	friend class WT_Opcode;

public:

    /// Constructs a WT_Polytriangle object.
    WT_Polytriangle ()
    { }

    /// Constructs a WT_Polytriangle object from the given data.
    WT_Polytriangle(
        int                         count, /**< The number of points in the array. */
        WT_Logical_Point const *    points, /**< Pointer to the array of points. */
        WT_Boolean                  copy /**< Whether the points should be copied or if their addresses should be used directly from the array. */
        ) 
        : WT_Point_Set(count, points, copy)
    { }

	WT_Polytriangle(WT_Polytriangle const& polytriangle) 
		: WT_Drawable()
        , WT_Point_Set(polytriangle.count(), polytriangle.points(), !!polytriangle.allocated())
	{ }

    /// Destroys a WT_Polytriangle object.
    virtual ~WT_Polytriangle()
    { }
public:
    //@{ \name WT_Object and WT_Drawable virtual methods
    virtual WT_Result   delay(WT_File & file) const;
    virtual WT_Result   dump(WT_File & file) const;
    WT_Result        materialize(WT_Opcode const & opcode, WT_File & file);
    virtual WT_Boolean  merge(WT_Drawable const & current);
    WT_ID            object_id() const;
    WT_Result        process(WT_File & file);
    WT_Result        serialize(WT_File & file) const;
    WT_Result        skip_operand(WT_Opcode const & opcode, WT_File & file);
    virtual void     update_bounds(WT_File * file);
    //@}

    /// Provides a default action handler for this object.
    /** \warning This is used by the framework and should not be called by client code.
     */
    static WT_Result default_process(
        WT_Polytriangle & item, /**< The object to process. */
        WT_File & file /**< The file being read. */
        );
};

//@}

#endif // POLYTRI_HEADER
