/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2016 Jean-David Gadina - www-xs-labs.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/*!
 * @header      CFNotificationCenter.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 * @discussion  A CFNotificationCenter object provides the means by which you
 *              can send a message, or notification, to any number of
 *              recipients, or observers, without having to know anything about
 *              the recipients. A notification message consists of a
 *              notification name (a CFString), a pointer value that identifies
 *              the object posting the notification, and an optional dictionary
 *              that contains additional information about the particular
 *              notification.
 *              To register as an observer of a notification, you call
 *              CFNotificationCenterAddObserver, providing an identifier for
 *              your observer, the callback function that should be called when
 *              the notification is posted, and the name of the notification and
 *              the object in which you are interested. The observer identifier
 *              is passed back to the callback function, along with the
 *              notification information. You can use the identifier to
 *              distinguish multiple observers using the same callback function.
 *              The identifier is also used to unregister the observer with
 *              CFNotificationCenterRemoveObserver and
 *              CFNotificationCenterRemoveEveryObserver.
 *              To send a notification, you call
 *              CFNotificationCenterPostNotification, passing in the
 *              notification information. The notification center then looks up
 *              all the observers that registered for this notification and
 *              sends the notification information to their callback functions.
 *              There are three types of CFNotificationCenter—a distributed
 *              notification center, a local notification center, and a Darwin
 *              notification center—an application may have at most one of each
 *              type. The distributed notification is obtained with
 *              CFNotificationCenterGetDistributedCenter. A distributed
 *              notification center delivers notifications between applications.
 *              In this case, the notification object must always be a CFString
 *              object and the notification dictionary must contain only
 *              property list values. The local and Darwin notification centers
 *              are available in OS X version 10.4 and later, and obtained
 *              using CFNotificationCenterGetLocalCenter and
 *              CFNotificationCenterGetDarwinNotifyCenter respectively.
 *              Unlike some other Core Foundation opaque types with names
 *              similar to a Cocoa Foundation class (such as CFString and
 *              NSString), CFNotificationCenter objects cannot be cast
 *              ("toll-free bridged") to NSNotificationCenter objects or
 *              vice-versa.
 */

#ifndef CORE_FOUNDATION_CF_NOTIFICATION_CENTER_H
#define CORE_FOUNDATION_CF_NOTIFICATION_CENTER_H

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFType.h>
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFDictionary.h>

CF_EXTERN_C_BEGIN

/*!
 * @typedef     CFNotificationCenterRef
 * @abstract    The type of a reference to a CFNotificationCenter.
 */
typedef struct CFNotificationCenter * CFNotificationCenterRef;

/*!
 * @typedef     CFNotificationName
 */
typedef CFStringRef CFNotificationName;

/*!
 * @typedef     CFNotificationCallback
 * @abstract    Callback function invoked for each observer of a notification
 *              when the notification is posted.
 * @param       center      The notification center handling the notification.
 * @param       observer    An arbitrary value, other than NULL, that identifies
 *                          the observer.
 * @param       name        The name of the notification being posted.
 * @param       object      An arbitrary value that identifies the object
 *                          posting the notification. For distributed
 *                          notifications, object is always a CFString object.
 *                          This value could be NULL.
 * @param       userInfo    A dictionary containing additional information
 *                          regarding the notification. This value could be
 *                          NULL.
 *                          If the notification center is a Darwin notification
 *                          center, this value must be ignored.
 */
typedef void ( * CFNotificationCallback )( CFNotificationCenterRef center, void * observer, CFNotificationName name, const void * object, CFDictionaryRef userInfo );

/*!
 * @typedef     CFNotificationSuspensionBehavior
 * @abstract    Suspension flags that indicate how distributed notifications
 *              should be handled when the receiving application is in the
 *              background.
 * @constant    CFNotificationSuspensionBehaviorDrop                The server will not queue any notifications of the
 *                                                                  specified name and object while the receiving
 *                                                                  application is in the background.
 * @constant    CFNotificationSuspensionBehaviorCoalesce            The server will only queue the last notification of
 *                                                                  the specified name and object; earlier notifications
 *                                                                  are dropped.
 * @constant    CFNotificationSuspensionBehaviorHold                The server will hold all matching notifications until
 *                                                                  the queue has been filled (queue size determined by
 *                                                                  the server) at which point the server may flush queued
 *                                                                  notifications.
 * @constant    CFNotificationSuspensionBehaviorDeliverImmediately  The server will deliver notifications of the specified
 *                                                                  name and object whether or not the application is in the
 *                                                                  background. When a notification with this suspension
 *                                                                  behavior is matched, it has the effect of first flushing
 *                                                                  any queued notifications.
 * @discussion  An application selects the suspension behavior for a given
 *              notification when it registers an observer for that notification
 *              with CFNotificationCenterAddObserver.
 */
typedef enum
{
    CFNotificationSuspensionBehaviorDrop                = 1,
    CFNotificationSuspensionBehaviorCoalesce            = 2,
    CFNotificationSuspensionBehaviorHold                = 3,
    CFNotificationSuspensionBehaviorDeliverImmediately  = 4
}
CFNotificationSuspensionBehavior;

/*!
 * @enum
 * @abstarct    Possible options when posting notifications.
 * @constanct   kCFNotificationDeliverImmediately   Delivers the notification immediately.
 * @constanct   kCFNotificationPostToAllSessions    Delivers the notification to all sessions.
 * @discussion  Use these constants when calling the
 *              CFNotificationCenterPostNotificationWithOptions function.
 */
enum
{
    kCFNotificationDeliverImmediately = ( 1UL << 0 ),
    kCFNotificationPostToAllSessions  = ( 1UL << 1 )
};

/*!
 * @function    CFNotificationCenterGetTypeID
 * @abstract    Returns the type identifier for the CFNotificationCenter opaque
 *              type.
 * @result      The type identifier for the CFNotificationCenter opaque type.
 */
CF_EXPORT CFTypeID CFNotificationCenterGetTypeID( void );

/*!
 * @function    CFNotificationCenterGetDarwinNotifyCenter
 * @abstract    Returns the application’s Darwin notification center.
 * @result      The application’s Darwin notification center.
 * @discussion  This notification center is used to cover the <notify.h> Core OS
 *              notification mechanism (see /usr/include/notify.h).
 *              An application has only one Darwin notification center, so this
 *              function returns the same value each time it is called.
 *              The Darwin Notify Center has no notion of per-user sessions,
 *              all notifications are system-wide. As with distributed
 *              notifications, the main thread's run loop must be running in
 *              one of the common modes (usually kCFRunLoopDefaultMode) for
 *              Darwin-style notifications to be delivered.
 *              Important: several function parameters are ignored by Darwin
 *              notification centers. To ensure future compatibility, you should
 *              pass NULL or 0 for all ignored arguments.
 */
CF_EXPORT CFNotificationCenterRef CFNotificationCenterGetDarwinNotifyCenter( void );

/*!
 * @function    CFNotificationCenterGetDistributedCenter
 * @abstract    Returns the application’s distributed notification center.
 * @result      The application's distributed notification center.
 *              An application has only one distributed notification center,
 *              so this function returns the same value each time it is called.
 * @discussion  A distributed notification center delivers notifications between
 *              applications. A notification object used with a distributed
 *              notification center must always be a CFString object and the
 *              notification dictionary must contain only property list values.
 */
CF_EXPORT CFNotificationCenterRef CFNotificationCenterGetDistributedCenter( void );

/*!
 * @function    CFNotificationCenterGetLocalCenter
 * @abstract    Returns the application’s local notification center.
 * @result      The application's local notification center. An application has
 *              only one local notification center, so this function returns the
 *              same value each time it is called.
 */
CF_EXPORT CFNotificationCenterRef CFNotificationCenterGetLocalCenter( void );

/*!
 * @function    CFNotificationCenterPostNotification
 * @abstract    Posts a notification for an object.
 * @param       center              The notification center to post the
 *                                  notification.
 * @param       name                The name of the notification to post.
 *                                  This value must not be NULL.
 * @param       object              The object posting the notification.
 *                                  If NULL, the notification is sent only to
 *                                  observers that are observing all objects.
 *                                  In other words, only observers that
 *                                  registered for the notification with a NULL
 *                                  value for object will receive the
 *                                  notification.
 *                                  If you want to allow your clients to
 *                                  register for notifications using Cocoa APIs
 *                                  (see NSNotificationCenter), then object must
 *                                  be a Core Foundation or Cocoa object.
 *                                  For distributed notifications, object must
 *                                  be a CFString object.
 *                                  If center is a Darwin notification center,
 *                                  this value is ignored.
 * @param       userInfo            A dictionary passed to observers.
 *                                  You populate this dictionary with additional
 *                                  information describing the notification.
 *                                  For distributed notifications, the
 *                                  dictionary must contain only property list
 *                                  objects. This value may be NULL.
 *                                  If center is a Darwin notification center,
 *                                  this value is ignored.
 * @param       deliverImmediately  If true, the notification is delivered to
 *                                  all observers immediately, even if some
 *                                  observers are in suspended (background)
 *                                  applications and they requested different
 *                                  suspension behavior when registering for the
 *                                  notification. If false, each observer's
 *                                  requested suspension behavior is respected.
 *                                  If center is a Darwin notification center,
 *                                  this value is ignored.
 */
CF_EXPORT void CFNotificationCenterPostNotification( CFNotificationCenterRef center, CFNotificationName name, const void * object, CFDictionaryRef userInfo, Boolean deliverImmediately );

/*!
 * @function    CFNotificationCenterPostNotificationWithOptions
 * @abstract    Posts a notification for an object using specified options.
 * @param       center      The notification center to post the notification.
 * @param       name        The name of the notification to post. This value
 *                          must not be NULL.
 * @param       object      The object posting the notification. If NULL, the
 *                          notification is sent only to observers that are
 *                          observing all objects. In other words, only
 *                          observers that registered for the notification with
 *                          a NULL value for object will receive the
 *                          notification.
 *                          If you want to allow your clients to register for
 *                          notifications using Cocoa APIs (see
 *                          NSNotificationCenter), then object must be a Core
 *                          Foundation or Cocoa object.
 *                          For distributed notifications, object must be a
 *                          CFString object.
 *                          If center is a Darwin notification center, this
 *                          value is ignored.
 * @param       userInfo    A dictionary to pass to observers. You populate this
 *                          dictionary with additional information describing
 *                          the notification. For distributed notifications, the
 *                          dictionary must contain only property list objects.
 *                          Can be NULL.
 *                          If center is a Darwin notification center, this
 *                          value is ignored.
 * @param       options     Specifies if the notification should be posted
 *                          immediately, or to all sessions. See Notification
 *                          Posting Options for possible values.
 *                          If center is a Darwin notification center, this
 *                          value is ignored.
 */
CF_EXPORT void CFNotificationCenterPostNotificationWithOptions( CFNotificationCenterRef center, CFNotificationName name, const void * object, CFDictionaryRef userInfo, CFOptionFlags options );

/*!
 * @function    CFNotificationCenterAddObserver
 * @abstract    Registers an observer to receive notifications.
 * @param       center              The notification center to which to add the
 *                                  observer.
 * @param       observer            The observer. In OS X v10.3 and later, this
 *                                  parameter may be NULL.
 * @param       callBack            The callback function to call when object
 *                                  posts the notification named name.
 * @param       name                The name of the notification to observe.
 *                                  If NULL, callback is called for any
 *                                  notification posted by object.
 *                                  If center is a Darwin notification center,
 *                                  this value must not be NULL.
 * @param       object              The object to observe. For distributed
 *                                  notifications, object must be a CFString
 *                                  object. If NULL, callback is called when a
 *                                  notification named name is posted by any
 *                                  object.
 *                                  If center is a Darwin notification center,
 *                                  this value is ignored.
 * @param       suspensionBehavior  Flag indicating how notifications should be
 *                                  handled when the application is in the
 *                                  background.
 *                                  See CFNotificationSuspensionBehavior for
 *                                  the list of available values.
 *                                  If center is a Darwin notification center,
 *                                  this value is ignored.
 * @discussion  Notification delivery is registered for the main thread.
 *              If you need to control which thread processes a notification,
 *              your callback function must be able to forward the notification
 *              to the proper thread. You can use a CFMessagePort object or a
 *              custom CFRunLoopSource object to send notifications to the
 *              correct thread's run loop.
 */
CF_EXPORT void CFNotificationCenterAddObserver( CFNotificationCenterRef center, const void * observer, CFNotificationCallback callBack, CFStringRef name, const void * object, CFNotificationSuspensionBehavior suspensionBehavior );

/*!
 * @function    CFNotificationCenterRemoveEveryObserver
 * @abstract    Stops an observer from receiving any notifications from any
 *              object.
 * @param       center      The notification center from which to remove
 *                          observers.
 * @param       observer    The observer. This value must not be NULL.
 * @discussion  If you no longer want an observer to receive any notifications,
 *              perhaps because the observer is being deallocated, you can call
 *              this function to unregister the observer from all the
 *              notifications for which it had previously registered.
 */
CF_EXPORT void CFNotificationCenterRemoveEveryObserver( CFNotificationCenterRef center, const void * observer );

/*!
 * @function    CFNotificationCenterRemoveObserver
 * @abstract    Stops an observer from receiving certain notifications
 * @param       center      The notification center to modify.
 * @param       observer    The observer. This value must not be NULL.
 * @param       name        The name of the notification to stop observing. If
 *                          NULL, observer stops receiving callbacks for all
 *                          notifications posted by object.
 * @param       object      The object to stop observing. For distributed
 *                          notifications, object must be a CFString object.
 *                          If NULL, observer stops receiving callbacks for all
 *                          objects posting notifications named name.
 *                          If center is a Darwin notification center, this
 *                          value is ignored.
 */
CF_EXPORT void CFNotificationCenterRemoveObserver( CFNotificationCenterRef center, const void * observer, CFNotificationName name, const void * object );

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION_CF_NOTIFICATION_CENTER_H */
