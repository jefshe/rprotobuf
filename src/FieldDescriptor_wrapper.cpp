#include "rprotobuf.h"
#include "fieldtypes.h"

namespace rprotobuf {

	RCPP_XP_METHOD_0( FieldDescriptor_is_extension      , GPB::FieldDescriptor, is_extension)  
	RCPP_XP_METHOD_0( FieldDescriptor_number            , GPB::FieldDescriptor, number)  
	RCPP_XP_METHOD_0( FieldDescriptor_type              , GPB::FieldDescriptor, type )  
	RCPP_XP_METHOD_0( FieldDescriptor_cpp_type          , GPB::FieldDescriptor, cpp_type )  
	RCPP_XP_METHOD_0( FieldDescriptor_label             , GPB::FieldDescriptor, label )  
	RCPP_XP_METHOD_0( FieldDescriptor_is_repeated       , GPB::FieldDescriptor, is_repeated )  
	RCPP_XP_METHOD_0( FieldDescriptor_is_optional       , GPB::FieldDescriptor, is_optional )  
	RCPP_XP_METHOD_0( FieldDescriptor_is_required       , GPB::FieldDescriptor, is_required )  
	RCPP_XP_METHOD_0( FieldDescriptor_has_default_value , GPB::FieldDescriptor, has_default_value )  
	

#define RPB_HANDLE_CASE(__CPP__,__LC__)                           \
case CPPTYPE_##__CPP__:                                           \
	{                                                             \
		return Rcpp::wrap( d->default_value_##__LC__() );         \
		break ;                                                   \
	}

	RCPP_FUNCTION_1( SEXP, FieldDescriptor_default_value , Rcpp::XPtr<GPB::FieldDescriptor> d ){
		switch( d->cpp_type() ){
			
			RPB_HANDLE_CASE(INT32,int32)
			RPB_HANDLE_CASE(INT64,int64)
			RPB_HANDLE_CASE(UINT32,uint32)
			RPB_HANDLE_CASE(UINT64,uint64)
			RPB_HANDLE_CASE(DOUBLE,double)
			RPB_HANDLE_CASE(FLOAT,float)
			RPB_HANDLE_CASE(BOOL,bool)
			RPB_HANDLE_CASE(STRING,string)

			case CPPTYPE_ENUM:
				{
					return Rf_ScalarInteger( d->default_value_enum()->number() ) ;
					break ;
				}
			default: 
				break ;
		}
		return R_NilValue ;
	}
	
	RCPP_FUNCTION_1(S4_Descriptor, FieldDescriptor_message_type, Rcpp::XPtr<GPB::FieldDescriptor> d){
		if( d->cpp_type() != CPPTYPE_MESSAGE ){
			throw Rcpp::not_compatible( "not a message type field" )  ;
		}
		return S4_Descriptor( d->message_type() ) ;
	}
	
	RCPP_FUNCTION_1(S4_EnumDescriptor, FieldDescriptor_enum_type, Rcpp::XPtr<GPB::FieldDescriptor> d){
		if( d->cpp_type() != CPPTYPE_ENUM ){
			throwException( "not an enum type field", "NotEnumType" ); 
		}
		return S4_EnumDescriptor( d->enum_type() ) ;
	}
	
#undef RPB_HANDLE_CASE
	
} // namespace rprotobuf

